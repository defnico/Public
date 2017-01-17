#ifndef BST_H
#define BST_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

/*
 * A templated class for a Node in a search tree. This represents a node in a
 * normal binary search tree, but can also be extended in the future for other
 * kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
 * You do NOT need to implement any functionality or add additional data members
 * or helper functions.
 */
template <typename Key, typename Value> class Node {
public:
  // Constructor/destructor
  Node(const Key& key, const Value& value, Node<Key, Value>* parent);
  virtual ~Node();

  // Getters for the data in this node.
  const std::pair<Key, Value>& getItem() const;
  std::pair<Key, Value>& getItem();
  const Key& getKey() const;
  const Value& getValue() const;
  Key& getKey();
  Value& getValue();

  // These functions are virtual so that any derived classes, such as the
  // AVLNode, can be overwritten to return AVLNode pointers. This is one
  // of the many advantages to using getters/setters instead of public data
  // in a struct.
  virtual Node<Key, Value>* getParent() const;
  virtual Node<Key, Value>* getLeft() const;
  virtual Node<Key, Value>* getRight() const;

  // Setters for the nodes data.
  void setParent(Node<Key, Value>* parent);
  void setLeft(Node<Key, Value>* left);
  void setRight(Node<Key, Value>* right);
  void setValue(const Value& value);

protected:
  std::pair<Key, Value> item_;
  Node<Key, Value>* parent_;
  Node<Key, Value>* left_;
  Node<Key, Value>* right_;
};

/*
-----------------------------------------
Begin implementations for the Node class.
-----------------------------------------
*/

/*
 * Explicit constructor for a node.
 */
template <typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value,
                       Node<Key, Value>* parent)
    : item_(key, value), parent_(parent), left_(nullptr), right_(nullptr) {}

/*
 * Destructor, which does not need to do anything since the pointers inside of a
 * node are only used as references to existing nodes. The nodes pointed to by
 * parent/left/right are freed within the deleteAll() helper method in the
 * BinarySearchTree.
 */
template <typename Key, typename Value> Node<Key, Value>::~Node() {}

/*
 * A const getter for the item.
 */
template <typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const {
  return item_;
}

/*
 * A non-const getter for the item.
 */
template <typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem() {
  return item_;
}

/*
 * A const getter for the key.
 */
template <typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const {
  return item_.first;
}

/*
 * A const getter for the value.
 */
template <typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const {
  return item_.second;
}

/*
 * A non-const getter for the key.
 */
template <typename Key, typename Value> Key& Node<Key, Value>::getKey() {
  return item_.first;
}

/*
 * A non-const getter for the value.
 */
template <typename Key, typename Value> Value& Node<Key, Value>::getValue() {
  return item_.second;
}

/*
 * An implementation of the virtual function for retreiving the parent.
 */
template <typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const {
  return parent_;
}

/*
 * An implementation of the virtual function for retreiving the left child.
 */
template <typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const {
  return left_;
}

/*
 * An implementation of the virtual function for retreiving the right child.
 */
template <typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const {
  return right_;
}

/*
 * A setter for setting the parent of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) {
  parent_ = parent;
}

/*
 * A setter for setting the left child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) {
  left_ = left;
}

/*
 * A setter for setting the right child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) {
  right_ = right;
}

/*
 * A setter for the value of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) {
  item_.second = value;
}

/*
---------------------------------------
End implementations for the Node class.
---------------------------------------
*/

/*
 * A templated unbalanced binary search tree.
 */
template <typename Key, typename Value> class BinarySearchTree {
public:
  // Constructor/destructor.
  BinarySearchTree();
  ~BinarySearchTree();

  // A virtual insert function lets future derivations of this class implement
  // their specific insert logic.
  virtual void insert(const std::pair<Key, Value>& keyValuePair);

  // Deletes all nodes in the tree and resets for use.
  void clear();

  // Prints the contents of the tree in a nice format. Useful for debugging.
  void print() const;

  /*
   * An internal iterator class for traversing the contents of the BST.
   */
  class iterator {
  public:
    iterator();
    iterator(Node<Key, Value>* ptr);

    std::pair<Key, Value>& operator*();
    std::pair<Key, Value>* operator->();
    bool operator==(const iterator& rhs) const;
    bool operator!=(const iterator& rhs) const;
    iterator& operator=(const iterator& rhs);
    iterator& operator++();

  protected:
    // A pointer to the current node.
    Node<Key, Value>* current_;
  };

  // Access to data through iterators, just like you are used to with std::map,
  // std::set, std::vector, etc.
  iterator begin();
  iterator end();
  iterator find(const Key& key) const;

protected:
  Node<Key, Value>* internalFind(const Key& key) const;
  void printRoot(Node<Key, Value>* root) const;
  void deleteAll(Node<Key, Value>* root);

  // Main data member of the class.
  Node<Key, Value>* root_;
};

/*
---------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/*
 * Initialize the internal members of the iterator.
 * You can choose what kind of iterator the default constructor should create.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(nullptr) {}

/*
 * Initialize the internal members of the iterator.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value>* ptr)
    : current_(ptr) {}

/*
 * Provides access to the item.
 */
template <typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() {
  return current_->getItem();
}

/*
 * Provides access to the address of the item.
 */
template <typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() {
  return &(current_->getItem());
}

/*
 * Checks if 'this' iterator's internals have the same value as 'rhs'.
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::
operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const {
  return current_ == rhs.current_;
}

/*
 * Checks if 'this' iterator's internals have a different value as 'rhs'.
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::
operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const {
  return current_ != rhs.current_;
}

/*
 * Sets one iterator equal to another iterator.
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::
operator=(const BinarySearchTree<Key, Value>::iterator& rhs) {
  current_ = rhs.current_;
  return *this;
}

/*
 * Advances the iterator's location using an in-order traversal.
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator&
    BinarySearchTree<Key, Value>::iterator::operator++() {
  // We should not be trying to increment a null iterator.
  assert(current_ != nullptr);

  // If there is a right child then iterate to the smallest value to the right.
  if (current_->getRight() != nullptr) {
    current_ = current_->getRight();

    while (current_->getLeft() != nullptr) {
      current_ = current_->getLeft();
    }
  } else {
    // Else go up to the tree until we find the subtree as on the left.
    Node<Key, Value>* p = current_->getParent();
    while (p != nullptr && current_ == p->getRight()) {
      current_ = p;
      p = p->getParent();
    }
    current_ = p;
  }
  return *this; // A dummy return value until you provide your implementation.
}

/*
 -------------------------------------------------------------
 End implementations for the BinarySearchTree::iterator class.
 -------------------------------------------------------------
*/

/*
 -----------------------------------------------------
 Begin implementations for the BinarySearchTree class.
 -----------------------------------------------------
*/

/*
 * Default constructor for a BinarySearchTree, which sets the root to nullptr.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(nullptr) {}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
  deleteAll(root_);
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const {
  printRoot(root_);
  std::cout << "\n";
}

/*
 * Returns an iterator to the "smallest" item in the tree
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() {
  // Find the leftmost node.
  Node<Key, Value>* current = root_;

  if (current != nullptr) {
    while (current->getLeft() != nullptr) {
      current = current->getLeft();
    }
  }
  return iterator(current);
}

/*
 * Returns an iterator whose value means INVALID
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() {
  // Return the default constructed iterator which has current set to null.
  return iterator();
}

/*
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key& key) const {
  return iterator(internalFind(key));
}

/*
 * An insert method to insert into a Binary Search Tree. The tree will not
 * remain balanced when inserting.  Implementing this will help you test your
 * iterator, but is not necessary: if you don't implement it, then you can put
 * your entire insert implementation in avlbst.h
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(
    const std::pair<Key, Value>& keyValuePair) {
  const Key& key = keyValuePair.first;
  const Value& value = keyValuePair.second;
  Node<Key, Value>* current = root_;
  Node<Key, Value>* parent = nullptr;
  while (current) {
    if (current->getKey() == key) {
      current->setValue(value);
      return;
    } else if (key < current->getKey()) {
      parent = current;
      current = current->getLeft();
    } else {
      parent = current;
      current = current->getRight();
    }
  }
  Node<Key, Value>* newNode = new Node<Key, Value>(key, value, parent);
  if (root_ == nullptr) {
    root_ = newNode;
  } else if (key < parent->getKey()) {
    parent->setLeft(newNode);
  } else {
    parent->setRight(newNode);
  }
}

/*
 * A method to remove all contents of the tree and reset the values in the tree
 * for use again.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() {
  deleteAll(root_);
  root_ = nullptr;
}

/*
 * Helper function to find a node with given key, k and return a pointer to it
 * or nullptr if no item with that key exists.
 */
template <typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::internalFind(const Key& key) const {
  Node<Key, Value>* current = root_;
  while (current) {
    if (current->getKey() == key) {
      return current;
    } else if (key < current->getKey()) {
      current = current->getLeft();
    } else {
      current = current->getRight();
    }
  }
  return nullptr;
}

/*
 * Helper function to print the tree's contents.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot(Node<Key, Value>* root) const {
  if (root != nullptr) {
    std::cout << "[";
    printRoot(root->getLeft());
    std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
    printRoot(root->getRight());
    std::cout << "]";
  }
}

/*
 * Helper function to delete all the items
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteAll(Node<Key, Value>* root) {
  if (root != nullptr) {
    deleteAll(root->getLeft());
    deleteAll(root->getRight());
    delete root;
  }
}

/*
 ---------------------------------------------------
 End implementations for the BinarySearchTree class.
 ---------------------------------------------------
*/

#endif
