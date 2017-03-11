#ifndef __LDE_h__
#define __LDE_h__

#include <string>
#include "module.h"
#include "common.h"

class LDE : public Module {
  public:
    LDE() : Module("LDE") {
      RegModule(this);
    }

    LDE(std::string name, WType wtype) 
      : Module("LDE", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new LDE(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __LDE_H__ */

