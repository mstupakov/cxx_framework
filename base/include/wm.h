#ifndef __WM_H__
#define __WM_H__

#include <iostream>
#include <string>
#include <vector>
#include "args.h"
#include "wpool.h"
#include "work.h"
#include "common.h"
#include "module.h"
#include "executer.h"
#include "thread.h"
#include "timer.h"

#define NUM_OF_WORKERS 3
#define CICLES_PER_SEC 10

class WM {

  bool m_run;

  Args m_args;
  Executer* m_executer;
  std::vector<Module*> m_modules;

  struct BlockInfo {
    std::string type;
    std::string name;
    bool sync;
  };
  
  struct ConnInfo {
    std::string name_what;
    std::string name_with;
    bool direction;
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

      m_executer = new Executer(workers);
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

  protected:
    int DoWork(Work* work, WType sync = SYNC) {
      return m_executer->DoWork(work, sync);
    }

  private:
    int Init();
    int DeInit();

    void ParseGv(std::string name);
    void ShowModules();

    void GetConnInfo(std::string line);
    void GetBlockInfo(std::string line);

    void CreateInfrastructure();

    Module* CreateModule(std::string type, std::string name, WType wtype) {
      return Module::CreateModule(type, name, wtype, &m_args, m_executer);
    }

    void RegModule(Module* module) {
      m_modules.push_back(module);
    }

    Module* GetModuleByName(std::string module) {
      for (auto it = m_modules.begin(); it != m_modules.end(); ++it) {
        if (module == (*it)->GetName()) {
          return *it;
        }
      }

      throw Error();
    }

    void MainLoop() {

      std::for_each(m_modules.begin(), m_modules.end(), 
                    [this](Module* m) { m->Notify(PHASE_RUNNING); });

      while (m_run) {
        double start = SYS::GetCurrentTime();

        std::for_each(m_modules.begin(), m_modules.end(), 
                      [this](Module* m) { m->Update(); });

        std::cout << "! Func: " << __PRETTY_FUNCTION__ << ", ms: " << start << std::endl;
        SYS::USleep(start + 1000000 / CICLES_PER_SEC - SYS::GetCurrentTime());
      }

      std::for_each(m_modules.begin(), m_modules.end(), 
                    [this](Module* m) { m->Notify(PHASE_STOP); });
    }
};

#endif /* __WM_H__ */

