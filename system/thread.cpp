#include <map>
#include <utility>
#include <pthread.h>
#include "thread.h"
#include "error.h"

namespace SYS {

  struct ThreadInfo {
    pthread_t thread;
    pthread_attr_t attribute;
  };

  std::map<Thread, ThreadInfo*> thread_db;

  Thread CreateThread(void* (*task)(void*), void *arg) {

    pthread_t thread;
    pthread_attr_t attr;

    if (::pthread_attr_init(&attr)) {
      throw Error();
    }

    if (::pthread_create(&thread, &attr, task, arg)) {
      throw Error();
    }

    ThreadInfo* info = new ThreadInfo;
    info->thread = thread;
    info->attribute = attr;

    auto res = thread_db.insert(std::make_pair(static_cast<Thread>(info), info));
    if (!res.second) {
      throw Error();
    }

    return res.first->second;
  }

}
