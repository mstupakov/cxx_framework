#ifndef __START_h__
#define __START_h__

#include <string>
#include "module.h"
#include "common.h"

class START : public Module {
  public:
    START() : Module("START") {
      RegModule(this);
    }

    START(MCloneInfo info) 
      : Module("START", info) {}

    virtual Module* Clone(MCloneInfo info) { 
      return new START(info); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {
      std::cout << "Module Name: "  << m_name 
        << ", Phase Name: " << phase << std::endl;
    }
};

#endif /* __START_H__ */

