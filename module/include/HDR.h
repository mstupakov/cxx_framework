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

    HDR(MCloneInfo info) 
      : Module("HDR", info) {}

    virtual Module* Clone(MCloneInfo info) { 
      return new HDR(info); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __HDR_H__ */

