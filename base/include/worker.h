#ifndef __WORKER_H__
#define __WORKER_H__

#include <iostream>
#include <string>
#include <functional>
#include "work.h"
#include "queue.h"
#include "thread.h"
#include "timer.h"

class Worker {
  std::string m_name;
  Queue<Work*> m_queue;

  public:
    Worker(std::string name) : m_name(name), m_queue(100) {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << 
        " Worker: " << m_name << std::endl;
      SYS::CreateThread(&Worker::Task, this);
    }

    void WakeUp(Work* work) {
      m_queue.PushBack(work);
    }

  private:
    static void* Task(void* arg) {
      Worker* worker = static_cast<Worker*>(arg);

      while (true) {
        if (worker->m_queue.IsEmpty()) {
          worker->m_queue.Wait();
        }

        Work* work = worker->m_queue.PopBegin();
        (*work)();
      }
      return NULL;
    }
};

#endif /* __WORKER_H__ */

