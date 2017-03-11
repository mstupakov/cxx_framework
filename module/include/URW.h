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

    URW(MCloneInfo info) 
      : Module("URW", info) {}

    virtual Module* Clone(MCloneInfo info) { 
      return new URW(info); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __URW_H__ */

