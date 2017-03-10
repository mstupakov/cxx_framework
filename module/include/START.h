#ifndef __START_h__
#define __START_h__

#include <string>
#include "module.h"

class START : public Module {
  public:
    START() : Module("START", "None") {
      RegModule(this);
    }

    START(std::string name) : Module("START", name) {}

    virtual Module* Clone(std::string name) { 
      return new START(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __START_H__ */

