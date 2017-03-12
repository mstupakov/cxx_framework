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

    PARSER(MCloneInfo info)
      : Module("PARSER", info) {}

    virtual Module* Clone(MCloneInfo info) {
      return CloneModule(this, info);
    }

    virtual void Update() {}
    virtual void Notify(Phase phase) {}
};

#endif /* __PARSER_H__ */

