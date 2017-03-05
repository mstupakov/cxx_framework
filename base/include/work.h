#ifndef __WORK_H__
#define __WORK_H__

#include <iostream>
#include <functional>

class Work {
  friend class WPool;
  std::function<void()> m_done;

  public:
    int operator()() {
      std::cout << "operator" << std::endl;
      //Done();
      return 0;
    }

  private:
    void Done() { m_done(); }
};

#endif /* __WORK_H__ */
