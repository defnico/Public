#ifndef _S16_SLIST_H__
#define _S16_SLIST_H__
#include <cstddef>
#include <iostream>

template <typename T> class slist {
public:
  slist();
  ~slist();

  struct Node {
    Node(T d, Node *n) : data(d), next(n) {}
    T data;
    Node *next;
  };

  void push_back(T x);
  void push_front(T x);
  void pop_back();
  void pop_front();
  int size();
  Node *tail();
  Node *head() { return head_; }

  void print() { print_recursive(head_); }
  void print_backwards() {
    print_backwards_recursive(head_);
    std::cout << std::endl;
  }

  T sum() { return sum_recusrsive(head_); }

  void remove_all(T x) { head_ = remove_all_recursive(head_, x); }

private:
  Node *head_;

  Node *remove_all_recursive(Node *n, T x) {
    if (n == nullptr) {
      return nullptr;
    }
    Node *t = remove_all_recursive(n->next, x);
    if (n->data != x) {
      n->next = t;
      return n;
    } else {
      delete n;
      return t;
    }
  }

  void print_recursive(Node *n) {
    if (n == nullptr) {
      std::cout << std::endl;
    } else {
      std::cout << n->data << " ";
      print_recursive(n->next);
    }
  }

  void print_backwards_recursive(Node *n) {
    if (n == nullptr) {
      return;
    } else {
      print_backwards_recursive(n->next);
      std::cout << n->data << " ";
    }
  }

  T sum_recusrsive(Node *n) {
    if (n == nullptr) {
      return T(0);
    } else {
      return n->value + sum_recusrsive(n->next);
    }
  }
};

// Print Out
template <typename T>
std::ostream &operator<<(std::ostream &os, slist<T> &list) {
  typename slist<T>::Node *node = list.head();
  while (node) {
    os << node->data << "  ";
    node = node->next;
  }
  return os;
}

// Constructor
template <typename T> slist<T>::slist() : head_(nullptr) {}

// Destructor
template <typename T> slist<T>::~slist() {
  Node *n = head_;
  while (n != nullptr) {
    Node *next = n->next;
    delete n;
    n = next;
  }
}

// Size
template <typename T> int slist<T>::size() {
  int count = 0;
  Node *n = head_;
  while (n != nullptr) {
    count++;
    n = n->next;
  }
  return count;
}

// Tail
template <typename T> typename slist<T>::Node *slist<T>::tail() {
  if (head_ == nullptr) {
    return nullptr;
  }
  Node *n = head_;
  while (n->next != nullptr) {
    n = n->next;
  }
  return n;
}

// Push Front
template <typename T> void slist<T>::push_front(T x) {
  head_ = new Node(x, head_);
}

// Push Back
template <typename T> void slist<T>::push_back(T x) {
  Node *n = new Node(x, nullptr);
  if (head_ == nullptr) {
    head_ = n;
  } else {
    tail()->next = n;
  }
}

// Pop Back
template <typename T> void slist<T>::pop_back() {
  if (head_ != nullptr) {
    Node *n = head_;
    Node *t = tail();
    if (n == t) {
      delete t;
      head_ = nullptr;
    } else {
      while (n->next != t) {
        n = n->next;
      }
      delete t;
      n->next = nullptr;
    }
  }
}

// Pop Front
template <typename T> void slist<T>::pop_front() {
  if (head_ != nullptr) {
    Node *n = head_->next;
    delete head_;
    head_ = n;
  }
}

#endif // _S16_SLIST_H__