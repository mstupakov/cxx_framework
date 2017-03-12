#ifndef __LDE_h__
#define __LDE_h__

#include <string>
#include "module.h"
#include "common.h"

class LDE : public Module {
  public:
    LDE() : Module("LDE") {
      RegModule(this);
    }

    LDE(MCloneInfo info)
      : Module("LDE", info) {}

    virtual Module* Clone(MCloneInfo info) {
      return CloneModule(this, info);
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __LDE_H__ */

