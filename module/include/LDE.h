#ifndef __LDE_h__
#define __LDE_h__

#include <string>
#include "module.h"

class LDE : public Module {
  public:
    LDE() : Module("LDE", "None") {
      RegModule(this);
    }

    LDE(std::string name) : Module("LDE", name) {}

    virtual Module* Clone(std::string name) { 
      return new LDE(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __LDE_H__ */

