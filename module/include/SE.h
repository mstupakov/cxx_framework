#ifndef __SE_h__
#define __SE_h__

#include <string>
#include "module.h"
#include "common.h"

class SE : public Module {
  public:
    SE() : Module("SE") {
      RegModule(this);
    }

    SE(std::string name, WType wtype) 
      : Module("SE", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new SE(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __SE_H__ */

