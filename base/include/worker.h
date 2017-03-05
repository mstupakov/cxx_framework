#ifndef __WORKER_H__
#define __WORKER_H__

#include <iostream>
#include <string>
#include "work.h"

class Worker {
  std::string m_name;

  public:
    Worker(std::string name) : m_name(name) {
      std::cout << "Name: " << m_name << std::endl;
    }

    void WakeUp(Work* work) {
     (*work)();
    }
};

#endif /* __WORKER_H__ */

