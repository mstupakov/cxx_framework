#ifndef __LOCK_H__
#define __LOCK_H__

class Lock {
  bool m_state;

  public:
    Lock(bool state = false): m_state(state) {}
    void Take() {}
    void Give() {}

    bool TryTake() { return true; }
};

#endif /* __LOCK_H__ */

