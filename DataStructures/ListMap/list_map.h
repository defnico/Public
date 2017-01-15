#ifndef _S16_LIST_MAP_H__
#define _S16_LIST_MAP_H__
#include "./dlist.h"
#include "./key_value.h"
#include <ostream>

template <typename K, typename V> class list_map {
public:
  list_map() {}
  ~list_map() {}

  class iter {
  public:
    iter() : node_(nullptr) {}
    iter(typename dlist<key_value<K, V> >::Node *n) : node_(n) {}
    ~iter() {}
    bool operator==(const iter &other) { return node_ == other.node_; }
    bool operator!=(const iter &other) { return node_ != other.node_; }
    key_value<K, V> &data() { return node_->value; }
    iter next() { return iter(node_ != nullptr ? node_->next : nullptr); }

  private:
    typename dlist<key_value<K, V> >::Node *node_;
  };

  iter begin();         // Construct an iter to the first element
  iter end();           // Construct an iter one past the last element
  iter find(K x);       // Construct an iter with value x
  bool remove(iter it); // Return true if found
  iter insert(key_value<K, V> kv);    // Insert x and return the iterator for x
                                      // Returns n if already in the set
  bool empty() { return c_.empty(); } // Checks if set if empty
  int size() { return c_.size(); }

private:
  dlist<key_value<K, V> > c_;
};

template <typename K, typename V>
typename list_map<K, V>::iter list_map<K, V>::begin() {
  return iter(c_.head());
}

template <typename K, typename V>
typename list_map<K, V>::iter list_map<K, V>::end() {
  return iter(nullptr);
}

template <typename K, typename V>
typename list_map<K, V>::iter list_map<K, V>::find(K key) {
  iter i = begin();
  while (i != end()) {
    if (i.data().key == key) {
      return i;
    }
    i = i.next();
  }
  return end();
}

template <typename K, typename V>
typename list_map<K, V>::iter list_map<K, V>::insert(key_value<K, V> kv) {
  iter i = find(kv.key);
  if (i != end()) {
    return i;
  } else {
    c_.push_back(kv);
    return iter(c_.tail());
  }
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, list_map<K, V> &m) {
  typename list_map<K, V>::iter i = m.begin();
  while (i != m.end()) {
    os << i.data().key << "->" << i.data().value;
    i = i.next();
  }
  return os;
}

#endif // _S16_LIST_MAP_H__