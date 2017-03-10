#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>
#include <vector>
#include "common.h"
#include "error.h"

class Module {
  std::string m_type;
  std::string m_name;

  public:
    static Module* CreateModule(std::string type, std::string name) {
      for (auto it = m_modules.begin(); it != m_modules.end(); ++it) {
        if (type == (*it)->m_type) {
          return (*it)->Clone(name);
        }
      }

      throw Error();
    }

    virtual Module* Clone(std::string name) = 0;
    virtual void Update() = 0;
    virtual void Notify(Phase phase) = 0;

  protected:
    Module(std::string type, std::string name) 
      : m_type(type), m_name(name) {}

    static void RegModule(Module* m) {
      m_modules.push_back(m);
    }

  private:
    static std::vector<Module*> m_modules;
};

#endif /* __MODULE_H__ */

