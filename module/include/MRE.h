#ifndef __MRE_h__
#define __MRE_h__

#include <string>
#include "module.h"
#include "common.h"

class MRE : public Module {
  public:
    MRE() : Module("MRE") {
      RegModule(this);
    }

    MRE(std::string name, WType wtype) 
      : Module("MRE", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new MRE(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __MRE_H__ */

