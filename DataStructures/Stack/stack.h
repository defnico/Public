#ifndef _S16_STACK_H__
#define _S16_STACK_H__
#include "./vector.h"

template <typename T> class stack {
public:
  void push(T x) { c_.push_back(x); }
  void pop() { c_.pop_back(); }
  T &top() { return c_[c_.size() - 1]; }
  bool empty() { return c_.empty(); }

private:
  vector<T> c_;
};

#endif // _S16_DLIST_H__