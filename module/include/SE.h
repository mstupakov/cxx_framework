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

    SE(MCloneInfo info) 
      : Module("SE", info) {}

    virtual Module* Clone(MCloneInfo info) { 
      return new SE(info); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __SE_H__ */

