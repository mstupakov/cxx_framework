#ifndef __ISME_h__
#define __ISME_h__

#include <string>
#include "module.h"
#include "common.h"

class ISME : public Module {
  public:
    ISME() : Module("ISME") {
      RegModule(this);
    }

    ISME(std::string name, WType wtype) 
      : Module("ISME", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new ISME(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __ISME_H__ */

