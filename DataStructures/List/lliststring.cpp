#include "lliststring.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
using namespace std;

// Constructor
LListString::LListString() {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

// Destructor
LListString::~LListString() { clear(); }

/**
   * Assignment Operator (deep copy)
   */
LListString& LListString::operator=(const LListString& other) {
  clear();

  // Special case empty list.
  if (other.head_ == NULL) {
    head_ = tail_ = NULL;
    return *this;
  }

  head_ = new Item;
  head_->val = other.head_->val;
  head_->prev = NULL;
  head_->next = NULL;

  Item* other_item = other.head_->next;
  Item* prev_item = head_;
  while (other_item != NULL) {
    Item* item = new Item;
    item->val = other_item->val;
    item->prev = prev_item;
    item->next = NULL;
    prev_item->next = item;
    prev_item = item;
    other_item = other_item->next;
  }
  tail_ = prev_item;
  size_ = other.size_;

  return *this;
}

LListString::LListString(const LListString& other) {
  head_ = tail_ = NULL;
  *this = other;
}

// Returns size of the list
int LListString::size() const { return size_; }

// Checks if list is empty
bool LListString::empty() const { return (size_ == 0); }

// Inserts val at position pos
void LListString::insert(int pos, const std::string& val) {
  if (pos >= 0 && pos <= size_) { // Verifies position
    if (pos == 0) {
      Item* item = new Item; // Creates new item
      item->val = val;
      item->prev = NULL;
      item->next = head_;
      if (head_ != NULL) { // Empty list case
        head_->prev = item;
      } else {
        tail_ = item;
      }
      head_ = item;
    } else if (pos == size_) { // End of list case
      Item* item = new Item;
      item->val = val;
      item->prev = tail_;
      item->next = NULL;
      if (tail_ != NULL) {
        tail_->next = item;
      } else {
        head_ = item;
      }
      tail_ = item;
    } else { // Insertion at other position
      Item* item = new Item;
      item->val = val;
      Item* prev_item = getNodeAt(pos - 1);
      Item* next_item = prev_item->next;
      item->prev = prev_item;
      item->next = next_item;
      prev_item->next = item;
      next_item->prev = item;
    }
    size_++;
  }
}

// Removes node at pos
void LListString::remove(int pos) {
  if (empty() || pos < 0 || pos >= size()) { // Checks position
    return;
  } else if (pos == 0) { // Remove from front
    Item* new_head = head_->next;
    delete head_;
    head_ = new_head;
    if (head_ == NULL) {
      tail_ = NULL;
    } else {
      head_->prev = NULL;
    }
    size_--;
  } else if (pos == size() - 1) { // Remove from end
    Item* new_tail = tail_->prev;
    delete tail_;
    tail_ = new_tail;
    if (tail_ == NULL) {
      head_ = NULL;
    } else {
      tail_->next = NULL;
    }
    size_--;
  } else { // Remove from other position
    Item* item = getNodeAt(pos);
    item->prev->next = item->next;
    item->next->prev = item->prev;
    delete item;
    size_--;
  }
}

// Sets pos to val
void LListString::set(int pos, const std::string& val) {
  if (pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  getNodeAt(pos)->val = val;
}

// Gets value at pos
std::string& LListString::get(int pos) {
  if (pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  return getNodeAt(pos)->val;
}

// Gets value at pos
std::string const& LListString::get(int pos) const {
  if (pos < 0 || pos >= size_) {
    // thr/ow :("bad location");
  }
  return getNodeAt(pos)->val;
}

// Clears out list
void LListString::clear() {
  while (head_ != NULL) {
    Item* item = head_->next;
    delete head_;
    head_ = item;
  }
  tail_ = NULL;
  size_ = 0;
}

// Returns value at pos
LListString::Item* LListString::getNodeAt(int pos) const {
  if (pos >= 0 && pos < size_) {
    Item* item = head_;
    for (int i = 0; i < pos; i++) {
      item = item->next;
    }
    return item;
  } else {
    return NULL;
  }
}

LListString LListString::operator+(const LListString& other) const {
  // Make a copy of *this. Then make a copy of other. Link the tail of the
  // first copy
  // to the head of the second copy.  Return the first copy.
  // Special case when one or both are empty.
  LListString copy1(*this);
  LListString copy2(other);

  if (copy1.empty()) {
    return copy2;
  } else if (copy2.empty()) {
    return copy1;
  } else {
    copy1.tail_->next = copy2.head_;
    copy2.head_->prev = copy1.tail_;
    copy1.size_ += copy2.size_;
    copy1.tail_ = copy2.tail_;
    copy2.head_ = copy2.tail_ = NULL;
    return copy1;
  }
}

const std::string& LListString::operator[](int pos) const { return get(pos); }
