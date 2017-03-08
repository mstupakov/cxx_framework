#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include "args.h"
#include "wpool.h"
#include "work.h"
#include "thread.h"
#include "timer.h"

#define NUM_OF_WORKERS 3
#define CICLES_PER_SEC 10

class System {
  bool m_run;

  Args m_args;
  WPool* m_wpool;

  public:
    enum WType {
      SYNC,
      ASYNC
    };

    System(Args args) :
      m_run(false), m_args(args) {
      int workers = NUM_OF_WORKERS;

      if (m_args.Has("-w")) {
        workers = std::stoi(m_args.Get("-w"));
      }

      m_wpool = new WPool(workers);
    }

    int Run() {
      m_run = true;

      Init();
      MainLoop();
      DeInit();

      return 0;
    }

    void Stop() {
      m_run = false;
    }

    int DoWork(Work* work, WType sync = SYNC) {
      if (ASYNC == sync) {
        m_wpool->DoWork(work);
      } else {
        (*work)();
      }
    }

  private:
    int Init();
    int DeInit();

    void MainLoop() {
      int i = 0;

      while (m_run) {
        double start = SYS::GetCurrentTime();

        m_wpool->Update();

        std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
        SYS::USleep(start + 1000000 / CICLES_PER_SEC - SYS::GetCurrentTime());
      }
    }
};

#endif /* __SYSTEM_H__ */

