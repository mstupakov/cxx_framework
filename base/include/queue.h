#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <queue>
#include <unistd.h>
#include "mutex.h"

template<class T>
class Queue {
  int m_nfree;
  std::queue<T> m_container;
  SYS::Cond m_new_data;
  SYS::Lock m_lock;

  public:
    Queue(int n_size) : m_nfree(n_size) {
      m_new_data = SYS::InitCondition();
      m_lock = SYS::CreateMutex();
    }

    bool PushBack(T& element) {
      if (!m_nfree) {
        return false;
      }

      m_nfree--;
      m_container.push(element);
      SYS::WakeCondition(m_new_data);
      return true;
    }

    T PopBegin() {
      T element = m_container.front();
      m_container.pop();

      m_nfree++;
      return element;
    }

    bool IsEmpty() {
      return m_container.empty();
    }

    void Wait() {
      while (IsEmpty()) SYS::WaitCondition(m_new_data, m_lock);
    }
};

#endif /* __QUEUE_H__ */

