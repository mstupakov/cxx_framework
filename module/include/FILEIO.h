#ifndef __FILEIO_h__
#define __FILEIO_h__

#include <string>
#include "module.h"
#include "common.h"

class FILEIO : public Module {
  friend class FileIOWork;

  public:
    FILEIO() : Module("FILE") {
      RegModule(this);
    }

    FILEIO(MCloneInfo info)
      : Module("FILE", info) {}

    virtual Module* Clone(MCloneInfo info) {
      return CloneModule(this, info);
    }

    virtual void Update() {}
    virtual void Notify(Phase phase);

  private:
    void Init();
    void DeInit();
    void Running();
    void Stop();

    void MainLoop();
};

#endif /* __FILEIO_H__ */

