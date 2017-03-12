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

    MRE(MCloneInfo info)
      : Module("MRE", info) {}

    virtual Module* Clone(MCloneInfo info) {
      return CloneModule(this, info);
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __MRE_H__ */

