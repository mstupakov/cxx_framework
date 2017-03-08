#include <map>
#include <pthread.h>
#include "mutex.h"
#include "error.h"

namespace SYS {

  struct LockInfo {
    pthread_mutex_t lock;
  };

  std::map<Lock, LockInfo*> lock_db;

  Lock CreateMutex() {
    pthread_mutex_t lock;

    if (::pthread_mutex_init(&lock, NULL)) {
      throw Error();
    }

    LockInfo* info = new LockInfo;
    info->lock = lock;

    auto res = lock_db.insert(std::make_pair(static_cast<Lock>(info), info));
    if (!res.second) {
      throw Error();
    }

    return res.first->second;
  }

  void LockMutex(Lock lock) {
    if (::pthread_mutex_lock(&lock_db[lock]->lock)) {
      throw Error();
    }
  }

  void UnLockMutex(Lock lock) {
    if (::pthread_mutex_unlock(&lock_db[lock]->lock)) {
      throw Error();
    }
  }

  struct CondInfo {
    pthread_cond_t condition;
  };

  std::map<Cond, CondInfo*> condition_db;

  Cond InitCondition() {
    pthread_cond_t cond;

    if (::pthread_cond_init(&cond, NULL)) {
      throw Error();
    }

    CondInfo* info = new CondInfo;
    info->condition = cond;

    auto res = condition_db.insert(std::make_pair(static_cast<Cond>(info), info));
    if (!res.second) {
      throw Error();
    }

    return res.first->second;
  }

  void WakeCondition(Cond condition) {
    if (::pthread_cond_signal(&condition_db[condition]->condition)) {
      throw Error();
    }
  }

  void WaitCondition(Cond condition, Lock lock) {
    if (::pthread_cond_wait(&condition_db[condition]->condition, &lock_db[lock]->lock)) {
      throw Error();
    }
  }
};

