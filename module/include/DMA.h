#ifndef __DMA_h__
#define __DMA_h__

#include <string>
#include "module.h"
#include "common.h"

class DMA : public Module {
  public:
    DMA() : Module("DMA") {
      RegModule(this);
    }

    DMA(MCloneInfo info)
      : Module("DMA", info) {}

    virtual Module* Clone(MCloneInfo info) {
      return CloneModule(this, info);
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __DMA_H__ */

