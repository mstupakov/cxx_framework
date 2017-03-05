#ifndef __THREAD_H__
#define __THREAD_H__

namespace SYS {
  typedef void* Thread;

  Thread CreateThread(void* (*task)(void*), void *arg);
  void StopThread(Thread t);
};

#endif /* __THREAD_H__ */

