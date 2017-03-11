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

    ACM(std::string name, WType wtype) 
      : Module("ACM", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new ACM(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __ACM_H__ */

