#include <stdio.h>
#include <string.h>
#include <string>
#include "system.h"
#include "work.h"

class MyWork_1: public Work {
  public:
    virtual int Execute() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      SYS::Sleep(1);
      return 0;
    }
};

class MyWork_2: public Work {
  public:
    virtual int Execute() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      SYS::Sleep(2);
      return 0;
    }
};

class MyWork_3: public Work {
  public:
    virtual int Execute() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      SYS::Sleep(2);
      return 0;
    }
};

class MyWork_4: public Work {
  System* sys;

  public:
    MyWork_4(System* system)
      : sys(system) {  }

    virtual int Execute() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
      sys->DoWork(new MyWork_3(), System::ASYNC);
      sys->DoWork(new MyWork_3(), System::SYNC);
      return 0;
    }
};

class MyWork_5: public Work {
  std::string str;

  public:
    MyWork_5(std::string name)
      : str(name) {
        //std::cout << str << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
    }

    virtual int Execute() {
      char arr[100];
     // std::cout << "! Func: " << __PRETTY_FUNCTION__ <<
       // " Name: " << str << std::endl;
      volatile int i = 0;
      for (i = 0; i < 999; i++) {}
      memset(arr, 0, sizeof(arr));
      sprintf(arr, "%s, %d", str.c_str(), i);
      return 0;
    }
};

class MyWorkStop: public Work {
  System* sys;

  public:
    MyWorkStop(System* system)
      : sys(system) {  }

    virtual int Execute() {
      sys->Stop();
    }
};

int System::Init() {

  Work* ww_1 = new Work();
//  DoWork(ww_1, SYNC);
//  DoWork(ww_1, ASYNC);

  MyWork_1* mm_1 = new MyWork_1();
//  DoWork(mm_1, SYNC);
//  DoWork(mm_1, ASYNC);

  MyWork_2* mm_2 = new MyWork_2();
//  DoWork(mm_2, SYNC);
//  DoWork(mm_2, ASYNC);

  for (int i = 0; i < 950000; i++) {
    DoWork(new MyWork_5("a") /*std::string("My Work: ") + std::to_string(i))*/, ASYNC);
  }

//  DoWork(new MyWork_4(this));
  DoWork(new MyWorkStop(this), ASYNC);
  return 0;
}

int System::DeInit() {
  std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
  return 0;
}

