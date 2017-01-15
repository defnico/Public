#ifndef _S16_QUEUE_H__
#define _S16_QUEUE_H__
#include "./dlist.h"

template <typename T> class queue {
public:
  void push(T x) { c_.push_back(x); }
  void pop() { c_.pop_front(); }
  T &front() { return c_.head()->value; }
  bool empty() { return c_.empty(); }

private:
  dlist<T> c_;
};

#endif // _S16_QUEUE_H__