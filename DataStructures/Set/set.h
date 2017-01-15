#ifndef _S16_SET_H__
#define _S16_SET_H__
#include "./dlist.h"
#include <ostream>

template <typename T> class set {
public:
  set() {}
  ~set() {}

  class iter {
  public:
    iter() : node_(nullptr) {}
    iter(typename dlist<T>::Node *n) : node_(n) {}
    ~iter() {}
    bool operator==(const iter &other) { return node_ == other.node_; }
    bool operator!=(const iter &other) { return node_ != other.node_; }
    T &value() { return node_->value; }
    iter next() { return iter(node_ != nullptr ? node_->next : nullptr); }

  private:
    typename dlist<T>::Node *node_;
  };

  iter begin();         // Construct an iter to the first element
  iter end();           // Construct an iter one past the last element
  iter find(T x);       // Construct an iter with value x
  bool remove(iter it); // Return true if found
  iter insert(T x);     // Insert x and return the iterator for x
                        // Returns n if already in the set
  bool empty() { return c_.empty(); } // Checks if set if empty
  int size() { return c_.size(); }

private:
  dlist<T> c_;
};

template <typename T> std::ostream &operator<<(std::ostream &os, set<T> &s) {
  typename set<T>::iter i = s.begin();
  while (i != s.end()) {
    os << i.value() << " ";
    i = i.next();
  }
  return os;
}

template <typename T> typename set<T>::iter set<T>::begin() {
  return iter(c_.head());
}

template <typename T> typename set<T>::iter set<T>::end() {
  return iter(nullptr);
}

template <typename T> typename set<T>::iter set<T>::find(T x) {
  iter i = begin();
  while (i != end()) {
    if (i.value() == x) {
      return i;
    }
    i = i.next();
  }
  return end();
}

template <typename T> typename set<T>::iter set<T>::insert(T x) {
  iter i = find(x);
  if (i != end()) {
    return i;
  } else {
    c_.push_back(x);
    return iter(c_.tail());
  }
}

#endif // _S16_SET_H__