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

    MME(MCloneInfo info) 
      : Module("MME", info) {}

    virtual Module* Clone(MCloneInfo info) { 
      return new MME(info); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __MME_H__ */

