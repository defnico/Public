#include <iostream>
#include <cstddef>
#include "delist.h"
using namespace std;

DEList::DEList() {
  head = nullptr;
  tail = nullptr;
}

DEList::~DEList() {
  DEItem* n = head;
  while (n != nullptr) {
    DEItem* m = n->next;
    delete n;
    n = m;
  }
  head = nullptr;
  tail = nullptr;
}

bool DEList::empty() {
  return (head == nullptr);
}

void DEList::push_back(int new_val) {
  DEItem* n = new DEItem;
  n->val = new_val;
  if (head == nullptr) {
    head = n;
    tail = n;
    n->next = nullptr;
    n->prev = nullptr;
  } else {
    tail->next = n;
    n->prev = tail;
    n->next = nullptr;
    tail = n;
  }
}

void DEList::pop_back() {
  if (head == nullptr) {
    return;
  } else if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    DEItem* n = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete n;
  }
}

void DEList::push_front(int new_val) {
  DEItem* n = new DEItem;
  n->val = new_val;
  if (head == nullptr) {
    head = n;
    tail = n;
    head->prev = nullptr;
    tail->prev = nullptr;
  } else {
    head->prev = n;
    n->next = head;
    n->prev = nullptr;
    head = n;
  }
}

void DEList::pop_front() {
  if (head == nullptr) {
    return;
  } else if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    DEItem* n = head;
    head = head->next;
    head->prev = nullptr;
    delete n;
  }
}

int DEList::size() {
  int count = 0;
  DEItem* n = head;
  while (n != nullptr) {
    n = n->next;
    count++;
  }
  return count;
}

int DEList::front() {
  if (head == nullptr) {
    return -1;
  } else {
    return head->val;
  }
}

int DEList::back() {
  if (tail == nullptr) {
    return -1;
  } else {
    return tail->val;
  }
}
