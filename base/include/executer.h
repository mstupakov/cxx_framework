#ifndef __EXECUTER_H__
#define __EXECUTER_H__

#include "common.h"
#include "work.h"
#include "wpool.h"

class Executer {
  WPool* m_wpool;

  public:
    Executer(int workers) {
      m_wpool = new WPool(workers);
    }

    int DoWork(Work* work, WType sync = SYNC) {
      if (ASYNC == sync) {
        m_wpool->DoWork(work);
      } else {
        (*work)();
      }
    }
};

#endif /* __EXECUTER_H__ */

