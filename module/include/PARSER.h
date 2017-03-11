#ifndef __PARSER_h__
#define __PARSER_h__

#include <string>
#include "module.h"
#include "common.h"

class PARSER : public Module {
  public:
    PARSER() : Module("PARSER") {
      RegModule(this);
    }

    PARSER(std::string name, WType wtype) 
      : Module("PARSER", name, wtype) {}

    virtual Module* Clone(std::string name, WType wtype) { 
      return new PARSER(name, wtype); 
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __PARSER_H__ */

