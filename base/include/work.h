#ifndef __WORK_H__
#define __WORK_H__

#include <iostream>
#include <functional>

class Work {
  friend class WPool;

  bool m_notify;
  std::function<void()> m_done;

  public:
    Work() : m_notify(false) {}

    int operator()() {
      int rc = Execute(); Done();
      return rc;
    }

    virtual int Execute() {
      std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
    }

  private:
    void RegWDone(std::function<void()> cb) { m_done = cb; m_notify = true; }
    void Done() { if (m_notify) m_done(); }
};

#endif /* __WORK_H__ */
