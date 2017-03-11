#ifndef __HDR_h__
#define __HDR_h__

#include <string>
#include "module.h"
#include "common.h"

class HDR : public Module {
  public:
    HDR() : Module("HDR") {
      RegModule(this);
    }

    HDR(std::string name, WType wtype) 
      : Module("HDR", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new HDR(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __HDR_H__ */

