#ifndef __MME_h__
#define __MME_h__

#include <string>
#include "module.h"

class MME : public Module {
  public:
    MME() : Module("MME", "None") {
      RegModule(this);
    }

    MME(std::string name) : Module("MME", name) {}

    virtual Module* Clone(std::string name) { 
      return new MME(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __MME_H__ */

