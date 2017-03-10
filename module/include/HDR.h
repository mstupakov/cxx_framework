#ifndef __HDR_h__
#define __HDR_h__

#include <string>
#include "module.h"

class HDR : public Module {
  public:
    HDR() : Module("HDR", "None") {
      RegModule(this);
    }

    HDR(std::string name) : Module("HDR", name) {}

    virtual Module* Clone(std::string name) { 
      return new HDR(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __HDR_H__ */

