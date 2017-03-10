#ifndef __URW_h__
#define __URW_h__

#include <string>
#include "module.h"

class URW : public Module {
  public:
    URW() : Module("URW", "None") {
      RegModule(this);
    }

    URW(std::string name) : Module("URW", name) {}

    virtual Module* Clone(std::string name) { 
      return new URW(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __URW_H__ */

