#ifndef __WORKER_H__
#define __WORKER_H__

#include <iostream>
#include <string>
#include <functional>
#include "work.h"
#include "thread.h"
#include "timer.h"

class Worker {
  std::string m_name;

  public:
    Worker(std::string name) : m_name(name) {
      std::cout << "Name: " << m_name << " " << this << std::endl;
      SYS::CreateThread(&Worker::Task, this);
    }

    void WakeUp(Work* work) {
     (*work)();
    }

  private:
    static void* Task(void* arg) {
      Worker* worker = static_cast<Worker*>(arg);

      std::cout << "Task: " << worker <<  "   " << arg << std::endl;
      while (1) {
        std::cout << "! Func: " << __PRETTY_FUNCTION__ << ", Name: " << worker->m_name << std::endl;
        SYS::USleep(1000);
      }
      return NULL;
    }
};

#endif /* __WORKER_H__ */

