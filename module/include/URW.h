#ifndef __URW_h__
#define __URW_h__

#include <string>
#include "module.h"
#include "common.h"

class URW : public Module {
  public:
    URW() : Module("URW") {
      RegModule(this);
    }

    URW(std::string name, WType wtype) 
      : Module("URW", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new URW(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __URW_H__ */

