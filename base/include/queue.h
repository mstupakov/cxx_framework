#ifndef __QUEUE_H__
#define __QUEUE_H__

template<class T>
class Queue {
  public:
    Queue(int n_size) {
    }

    bool PushBack(T& element) { return true; }
    T PopBegin() { return T(); }

    bool IsEmpty() { return true; }
};

#endif /* __QUEUE_H__ */

