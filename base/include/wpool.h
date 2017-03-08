#ifndef __WPOOL_H__
#define __WPOOL_H__

#include <vector>
#include <string>
#include <utility>
#include <functional>
#include "worker.h"
#include "work.h"
#include "lock.h"
#include "queue.h"
#include "error.h"

#define SIZE_OF_QUEUE 1000000

class WPool {
  struct WorkerInfo {
    bool m_busy;
    Worker* m_worker;
  };

  int m_nworker;
  int m_nworker_free;

  Lock m_lock;
  Queue<Work*> m_queue;
  std::vector<WorkerInfo> m_workers;

  public:
    WPool(int n_worker)
    : m_nworker(n_worker),
      m_nworker_free(n_worker),
      m_lock(false), m_queue(SIZE_OF_QUEUE) {
      for (int i = 0; i < n_worker; ++i) {
        WorkerInfo info = {
          .m_busy = false,
          .m_worker = new Worker(std::string("Worker_")
              + std::to_string(i))
        };

        m_workers.push_back(info);
      }
    }

    int DoWork(Work* work) {
      m_lock.Take();
      m_queue.PushBack(work);
      m_lock.Give();

      Schedule();
    }

    void Update() {
      Schedule();
    }

  private:
    void Schedule() {
      m_lock.Take();

      if (!m_queue.IsEmpty()) {
        do {
          WorkerInfo* info = FindFreeWorker();
          if (info) {
            m_nworker_free--;

            Work* work = m_queue.PopBegin();
            work->RegWDone(std::bind(&WPool::ReleaseWorker, this, info));

            info->m_busy = true;
            info->m_worker->WakeUp(work);
          }
        } while (!m_queue.IsEmpty() && m_nworker_free);
      }

      m_lock.Give();
    }

    WorkerInfo* FindFreeWorker() {
      if (m_nworker_free) {
        for (auto it = m_workers.begin(); it != m_workers.end(); ++it) {
          if (!it->m_busy) {
            return &(*it);
          }
        }
      }

      return NULL;
    }

    void ReleaseWorker(WorkerInfo* info) {

      m_lock.Take();
      info->m_busy = false;
      m_nworker_free++;
      m_lock.Give();

      Schedule();
    }
};

#endif /* __WPOOL_H__ */

