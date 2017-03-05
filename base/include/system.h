#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include "args.h"
#include "wpool.h"
#include "work.h"

class System {
  Args m_args;
  WPool m_wpool;

  public:
    enum WType {
      SYNC,
      ASYNC
    };

    System(Args args) : m_args(args), m_wpool(4) {
    }

    int Run() {
      std::cout << m_args.Has("-abc") << std::endl;

      Work ww;
      DoWork(ww, SYNC);
      DoWork(ww, ASYNC);
      return 0;
    }

    int DoWork(Work &work, WType sync = SYNC) {
      if (ASYNC == sync) {
        m_wpool.DoWork(work);
      } else {
        work();
      }
    }
};

#endif /* __SYSTEM_H__ */

