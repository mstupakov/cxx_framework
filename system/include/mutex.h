#ifndef __MUTEX_H__
#define __MUTEX_H__

namespace SYS {
  typedef void* Lock;

  Lock CreateMutex();
  void LockMutex(Lock lock);
  void UnLockMutex(Lock lock);

  typedef void* Cond;

  Cond InitCondition();
  void WakeCondition(Cond condition);
  void WaitCondition(Cond condition, Lock lock);
};

#endif /* __MUTEX_H__ */

