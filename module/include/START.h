#ifndef __START_h__
#define __START_h__

#include <string>
#include "module.h"
#include "common.h"

class START : public Module {
  public:
    START() : Module("START") {
      RegModule(this);
    }

    START(std::string name, WType wtype) 
      : Module("START", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new START(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __START_H__ */

