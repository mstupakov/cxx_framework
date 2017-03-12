#ifndef __ACM_h__
#define __ACM_h__

#include <string>
#include "module.h"
#include "common.h"

class ACM : public Module {
  public:
    ACM() : Module("ACM") {
      RegModule(this);
    }

    ACM(MCloneInfo info)
      : Module("ACM", info) {}

    virtual Module* Clone(MCloneInfo info) {
      return CloneModule(this, info);
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __ACM_H__ */

