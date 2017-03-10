#ifndef __ISME_h__
#define __ISME_h__

#include <string>
#include "module.h"

class ISME : public Module {
  public:
    ISME() : Module("ISME", "None") {
      RegModule(this);
    }

    ISME(std::string name) : Module("ISME", name) {}

    virtual Module* Clone(std::string name) { 
      return new ISME(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __ISME_H__ */

