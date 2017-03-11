#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>
#include <vector>
#include "common.h"
#include "error.h"
#include "transaction.h"

class Module {
  std::string m_type;
  std::string m_name;

  WType m_wtype;
  std::vector<Module*> m_connections;

  public:
    static Module* CreateModule(std::string type, std::string name, WType wtype) {
      for (auto it = m_modules.begin(); it != m_modules.end(); ++it) {
        if (type == (*it)->m_type) {
          return (*it)->Clone(name, wtype);
        }
      }

      throw Error();
    }

    std::string GetName() {
      return m_name;
    }

    void Connect(Module* module, bool direction) {
      m_connections.push_back(module);
    }

    virtual Module* Clone(std::string name, WType wtype) = 0;
    virtual void Update() = 0;
    virtual void Notify(Phase phase) = 0;

    virtual void Send(Transaction* tr) {}

  protected:
    Module(std::string type)
      : m_type(type) {}

    Module(std::string type, std::string name, WType wtype) 
      : m_type(type), m_name(name), m_wtype(wtype) {}

    static void RegModule(Module* m) {
      m_modules.push_back(m);
    }

  private:
    static std::vector<Module*> m_modules;
};

#endif /* __MODULE_H__ */

