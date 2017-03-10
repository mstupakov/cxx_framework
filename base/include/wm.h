#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include <string>
#include <vector>
#include "args.h"
#include "wpool.h"
#include "work.h"
#include "common.h"
#include "module.h"
#include "thread.h"
#include "timer.h"

#define NUM_OF_WORKERS 3
#define CICLES_PER_SEC 10

class WM {

  bool m_run;

  Args m_args;
  WPool* m_wpool;
  std::vector<Module*> m_modules;

  struct BlockInfo {
    std::string type;
    std::string name;
  };
  
  struct ConnInfo {
    std::string name_what;
    std::string name_with;
    bool is_direction_both;
    std::vector<std::string> labels;
  };

  std::vector<BlockInfo> m_blocks;
  std::vector<ConnInfo> m_connections;

  public:
    WM(Args args) :
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

    void ParseGv(std::string name);
    void ShowModules();

    void GetConnInfo(std::string line);
    void GetBlockInfo(std::string line);

    void CreateInfrastructure();

    Module* CreateModule(std::string type, std::string name) {
      return Module::CreateModule(type, name);
    }

    void RegModule(Module* module) {
      m_modules.push_back(module);
    }

    void MainLoop() {

      std::for_each(m_modules.begin(), m_modules.end(), 
                    [this](Module* m) { m->Notify(PHASE_RUNNING); });

      while (m_run) {
        double start = SYS::GetCurrentTime();

        m_wpool->Update();

        std::for_each(m_modules.begin(), m_modules.end(), 
                      [this](Module* m) { m->Update(); });

        std::cout << "! Func: " << __PRETTY_FUNCTION__ << ", ms: " << start << std::endl;
        SYS::USleep(start + 1000000 / CICLES_PER_SEC - SYS::GetCurrentTime());
      }

      std::for_each(m_modules.begin(), m_modules.end(), 
                    [this](Module* m) { m->Notify(PHASE_STOP); });
    }
};

#endif /* __SYSTEM_H__ */

