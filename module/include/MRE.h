#ifndef __MRE_h__
#define __MRE_h__

#include <string>
#include "module.h"

class MRE : public Module {
  public:
    MRE() : Module("MRE", "None") {
      RegModule(this);
    }

    MRE(std::string name) : Module("MRE", name) {}

    virtual Module* Clone(std::string name) { 
      return new MRE(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __MRE_H__ */

