#ifndef __MME_h__
#define __MME_h__

#include <string>
#include "module.h"
#include "common.h"

class MME : public Module {
  public:
    MME() : Module("MME") {
      RegModule(this);
    }

    MME(std::string name, WType wtype) 
      : Module("MME", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new MME(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __MME_H__ */

