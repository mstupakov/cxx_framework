#ifndef __ACM_h__
#define __ACM_h__

#include <string>
#include "module.h"

class ACM : public Module {
  public:
    ACM() : Module("ACM", "None") {
      RegModule(this);
    }

    ACM(std::string name) : Module("ACM", name) {}

    virtual Module* Clone(std::string name) { 
      return new ACM(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __ACM_H__ */

