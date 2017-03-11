#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>
#include <vector>
#include "args.h"
#include "common.h"
#include "error.h"
#include "transaction.h"
#include "executer.h"

class Module {
  protected:
    std::string m_type;
    std::string m_name;

    WType m_wtype;
    Args* m_args;

  private:
    Executer* m_executer;

    struct MConnInfo {
      Module* module;
      bool direction;
    };

  protected:
    std::vector<MConnInfo> m_connections;

  public:
    static Module* CreateModule(std::string type, 
        std::string name, WType wtype, Args* args, Executer* exec) {
      for (auto it = m_modules.begin(); it != m_modules.end(); ++it) {
        if (type == (*it)->m_type) {

          MCloneInfo info = {
            .name = name,
            .wtype = wtype,
            .args = args,
            .executer = exec
          };

          return (*it)->Clone(info);
        }
      }

      throw Error();
    }

    std::string GetName() {
      return m_name;
    }

    void Connect(Module* module, bool direction) {
      MConnInfo info = {
        .module = module,
        .direction = direction
      };

      m_connections.push_back(info);
    }

    struct MCloneInfo {
      std::string name;
      WType wtype;
      Args* args;
      Executer* executer;
    };

    virtual Module* Clone(MCloneInfo info) = 0;

    virtual void Update() = 0;
    virtual void Notify(Phase phase) = 0;

    virtual void Send(Transaction* tr) {
      m_executer->DoWork(tr, m_wtype);
    }

  protected:
    void DoWork(Work* work, WType wtype) {
      m_executer->DoWork(work, wtype);
    }

    Module(std::string type)
      : m_type(type) {}

    Module(std::string type, MCloneInfo info) 
      : m_type(type) {
        m_name = info.name;
        m_wtype = info.wtype;
        m_args = info.args;
        m_executer = info.executer;
      }

    static void RegModule(Module* m) {
      m_modules.push_back(m);
    }

  private:
    static std::vector<Module*> m_modules;
};

#endif /* __MODULE_H__ */

