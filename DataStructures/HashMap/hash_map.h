#ifndef _S16_HASH_MAP_H_
#define _S16_HASH_MAP_H_

#include "./key_value.h"
#include "./slist.h"
#include "./vector.h"
#include <ostream>
#include <string>

unsigned int DJBHash(const std::string &str) {
  unsigned int hash = 5381;

  for (int i = 0; i < str.size(); i++) {
    hash = ((hash << 5) + hash) + str[i];
  }
  return hash;
}

template <typename V> class hash_map {
public:
  hash_map(int n) { v_.resize(n); }
  ~hash_map() {}

  V& operator[](const std::string& key);

  V* find(const std::string& key);

private:
  typedef key_value<std::string, V> KV;
  typedef slist<KV> ListType;

  vector<ListType> v_;
};

template <typename V> V *hash_map<V>::find(const std::string& key) {
  int bucket = DJBHash(key) % v_.size();
  ListType &list = v_[bucket];

  typename ListType::Node *node = list.head();
  while (node != nullptr) {
    if (node->data.key == key) {
      return &node->data.value;
    } else {
      node = node->next;
    }
  }
  return nullptr;
}

template <typename V> V &hash_map<V>::operator[](const std::string& key) {
  int bucket = DJBHash(key) % v_.size();
  ListType &list = v_[bucket];

  typename ListType::Node *node = list.head();
  while (node != nullptr) {
    if (node->data.key == key) {
      return node->data.value;
    } else {
      node = node->next;
    }
  }
  list.push_front(KV(key, V()));
  return list.head()->data.value;
}

#endif // _S16_HASH_MAP_H__