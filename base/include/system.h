#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include "args.h"
#include "wpool.h"
#include "work.h"
#include "thread.h"
#include "timer.h"

class MyWork_1: public Work {
  public:
    virtual int Execute() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      return 0;
    }
};

class MyWork_2: public Work {
  public:
    virtual int Exectute() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      return 0;
    }
};

class System {
  bool m_run;

  Args m_args;
  WPool m_wpool;

  public:
    enum WType {
      SYNC,
      ASYNC
    };

    System(Args args) :
      m_run(false), m_args(args), m_wpool(4) {
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
        m_wpool.DoWork(work);
      } else {
        (*work)();
      }
    }

  private:
    int Init() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      std::cout << m_args.Has("-abc") << std::endl;

      Work* ww = new Work();
      DoWork(ww, SYNC);
      DoWork(ww, ASYNC);

      MyWork_1* mm1 = new MyWork_1();
      DoWork(mm1, SYNC);
      DoWork(mm1, ASYNC);

      MyWork_2* mm2 = new MyWork_2();
      DoWork(mm2, SYNC);
      DoWork(mm2, ASYNC);

      return 0;
    }

    int DeInit() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      return 0;
    }

    void MainLoop() {
      int i = 0;

      while (m_run) {

        m_wpool.Update();
        SYS::USleep(100);

        std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
        i++; if (i >= 150) Stop();
      }
    }
};

#endif /* __SYSTEM_H__ */

