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

    ISME(MCloneInfo info) 
      : Module("ISME", info) {}

    virtual Module* Clone(MCloneInfo info) { 
      return new ISME(info); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __ISME_H__ */

