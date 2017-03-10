#ifndef __SE_h__
#define __SE_h__

#include <string>
#include "module.h"

class SE : public Module {
  public:
    SE() : Module("SE", "None") {
      RegModule(this);
    }

    SE(std::string name) : Module("SE", name) {}

    virtual Module* Clone(std::string name) { 
      return new SE(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __SE_H__ */

