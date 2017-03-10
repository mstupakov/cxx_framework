#ifndef __PARSER_h__
#define __PARSER_h__

#include <string>
#include "module.h"

class PARSER : public Module {
  public:
    PARSER() : Module("PARSER", "None") {
      RegModule(this);
    }

    PARSER(std::string name) : Module("PARSER", name) {}

    virtual Module* Clone(std::string name) { 
      return new PARSER(name); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __PARSER_H__ */

