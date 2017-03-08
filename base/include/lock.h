#ifndef __LOCK_H__
#define __LOCK_H__

#include "mutex.h"

class Lock {
  SYS::Lock m_lock;

  public:
    Lock(bool state = false) {
      m_lock = SYS::CreateMutex();
      if (state) {
        Take();
      } else {
        Give();
      }
    }

    void Take() {
      SYS::LockMutex(m_lock);
    }

    void Give() {
      SYS::UnLockMutex(m_lock);
    }

    bool TryTake() { return true; }
};

#endif /* __LOCK_H__ */

