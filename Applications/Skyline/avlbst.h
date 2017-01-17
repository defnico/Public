#ifndef AVLBST_H
#define AVLBST_H

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <string>

/*
 * A special kind of node for an AVL tree, which adds the height as a data
 * member, plus other additional helper functions. You do NOT need to implement
 * any functionality or add additional data members or helper functions.
 */
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
  // Constructor/destructor.
  AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
  virtual ~AVLNode();

  // Getter/setter for the node's height.
  int getHeight() const;
  void setHeight(int height);

  int getLeftHeight() const {
    return (getLeft() == nullptr) ? 0 : getLeft()->height_;
  }

  int getRightHeight() const {
    return (getRight() == nullptr) ? 0 : getRight()->height_;
  }

  void fixHeight() {
    height_ = std::max(getLeftHeight(), getRightHeight()) + 1;
  }

  int getBalance() const { return getRightHeight() - getLeftHeight(); }

  // Getters for parent, left, and right. These need to be redefined since they
  // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
  // for more information.
  virtual AVLNode<Key, Value>* getParent() const override;
  virtual AVLNode<Key, Value>* getLeft() const override;
  virtual AVLNode<Key, Value>* getRight() const override;

protected:
  int height_;
};

/*
 --------------------------------------------
 Begin implementations for the AVLNode class.
 --------------------------------------------
 */

/*
 * Constructor for an AVLNode. Nodes are initialized with a height of 0.
 */
template <typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value,
                             AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent), height_(0) {}

/*
 * Destructor.
 */
template <typename Key, typename Value> AVLNode<Key, Value>::~AVLNode() {}

/*
 * Getter function for the height.
 */
template <typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const {
  return height_;
}

/*
 * Setter function for the height.
 */
template <typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height) {
  height_ = height;
}

/*
 * Getter function for the parent. Used since the node inherits from a base
 * node.
 */
template <typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const {
  return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/*
 * Getter function for the left child. Used since the node inherits from a base
 * node.
 */
template <typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const {
  return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/*
 * Getter function for the right child. Used since the node inherits from a base
 * node.
 */
template <typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const {
  return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
 ------------------------------------------
 End implementations for the AVLNode class.
 ------------------------------------------
*/

/*
 * A templated balanced binary search tree implemented as an AVL tree.
 */
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
  // Methods for inserting/removing elements from the tree. You must implement
  // both of these methods.
  virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
  void remove(const Key& key);

  // Print the heights.
  void printHeights();

  // Check the child parent pointers for debugging.
  void validateTree();

private:
  // Get andthe root of the tree.  Must be cast to AVLNode because it is
  // represented as just a Node in the base class.
  AVLNode<Key, Value>* getRoot() {
    return static_cast<AVLNode<Key, Value>*>(AVLTree<Key, Value>::root_);
  }
  const AVLNode<Key, Value>* getRoot() const {
    return static_cast<AVLNode<Key, Value>*>(AVLTree<Key, Value>::root_);
  }
  void setRoot(AVLNode<Key, Value>* newRoot) {
    AVLTree<Key, Value>::root_ = newRoot;
  }

  AVLNode<Key, Value>* rotateRight(AVLNode<Key, Value>* p);
  AVLNode<Key, Value>* rotateLeft(AVLNode<Key, Value>* q);

  void printRootHeights(AVLNode<Key, Value>* root);

  void validateSubtree(AVLNode<Key, Value>* root);
};

/*
 --------------------------------------------
 Begin implementations for the AVLTree class.
 --------------------------------------------
*/

// Right rotation about node p.  Returns root of rotated subtree.
template <class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* p) {
  // Let q be p's left child which will become the root of the rotated subtree.
  // To rotate right: set q's right child to p and
  // set p's left child to q's right child (T2).
  AVLNode<Key, Value>* q = p->getLeft();
  AVLNode<Key, Value>* T2 = q->getRight();

  // Set q's right child to p.
  q->setRight(p);

  // Set p's left child to q's right child.
  p->setLeft(T2);

  // Fix parent links.
  // Set q's parent to be p's old parent and fix q's new parent to point to q.
  // If p's parent is null then p was the root, so set q to be the new root.
  AVLNode<Key, Value>* pParent = p->getParent();
  q->setParent(pParent);
  if (pParent == nullptr) {
    setRoot(q);
  } else {
    if (pParent->getLeft() == p) {
      pParent->setLeft(q);
    } else {
      pParent->setRight(q);
    }
  }

  // p's parent is now q.
  p->setParent(q);

  // If not null, T2's parent is now p.
  if (T2 != nullptr) {
    T2->setParent(p);
  }

  p->fixHeight();
  q->fixHeight();

  return q;
}

// Left rotation about node q. Returns root of rotated subtree.
template <class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* q) {
  // Let p be q's right child which will become the root of the rotated subtree.
  // To rotate left: set p's left child to q and
  // set q's right child to p's left child (T2).
  AVLNode<Key, Value>* p = q->getRight();
  AVLNode<Key, Value>* T2 = p->getLeft();

  // Set p's left child to q.
  p->setLeft(q);

  // Set q's right child to p's left child.
  q->setRight(T2);

  // Fix parent links.
  // Set p's parent to be q's old parent and fix p's new parent to point to p.
  // If q's parent is null then q was the root, so set p to be the new root.
  AVLNode<Key, Value>* qParent = q->getParent();
  p->setParent(qParent);
  if (qParent == nullptr) {
    setRoot(p);
  } else {
    if (qParent->getLeft() == q) {
      qParent->setLeft(p);
    } else {
      qParent->setRight(p);
    }
  }

  // q's parent is now p.
  q->setParent(p);

  // If not null, T2's parent is now q.
  if (T2 != nullptr) {
    T2->setParent(q);
  }

  q->fixHeight();
  p->fixHeight();

  return p;
}

/*
 * Insert function for a key value pair. Finds location to insert the node and
 * then balances the tree.
 */
template <typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair) {
  // The insertion stage is the same as the bst.
  const Key& key = keyValuePair.first;
  const Value& value = keyValuePair.second;

  AVLNode<Key, Value>* current = getRoot();
  AVLNode<Key, Value>* parent = nullptr;
  while (current) {
    if (current->getKey() == key) {
      current->setValue(value);
      return; // No new node was inserted so just update value and return.
    } else if (key < current->getKey()) {
      parent = current;
      current = current->getLeft();
    } else {
      parent = current;
      current = current->getRight();
    }
  }
  AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(key, value, parent);
  if (getRoot() == nullptr) {
    setRoot(newNode);
  } else if (key < parent->getKey()) {
    parent->setLeft(newNode);
  } else {
    parent->setRight(newNode);
  }

  // Fix the heights and rotate the imbalanced ancestors.
  for (AVLNode<Key, Value>* p = newNode; p != nullptr; p = p->getParent()) {
    p->fixHeight();
    if (p->getBalance() == 2) {
      // The right side is deeper than the left so rotate left. But rotate right
      // the right subtree to bring up it's left subtree if needed.
      if (p->getRight()->getBalance() < 0) {
        rotateRight(p->getRight());
      }
      p = rotateLeft(p);
    } else if (p->getBalance() == -2) {
      // The left side is deeper than the right so rotate right. But rotate left
      // the left subtree to bring up it's right subtree if needed.
      if (p->getLeft()->getBalance() > 0) {
        rotateLeft(p->getLeft());
      }
      p = rotateRight(p);
    }
  }

  // Validate the state of the tree after this operation.
  // Remove this before turning in.
  // validateTree();
}

/*
 * Remove function for a given key. Finds the node, reattaches pointers, and
 * then balances when finished.
 */
template <typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key) {
  AVLNode<Key, Value>* p = getRoot();
  while (p) {
    if (p->getKey() == key) {
      break;
    } else if (key < p->getKey()) {
      p = p->getLeft();
    } else {
      p = p->getRight();
    }
  }
  if (p == nullptr) {
    return;
  }

  AVLNode<Key, Value>* pParent = p->getParent();
  AVLNode<Key, Value>* pLeft = p->getLeft();
  AVLNode<Key, Value>* pRight = p->getRight();

  // Replace p with child if there is only one child.
  if (pLeft == nullptr || pRight == nullptr) {
    AVLNode<Key, Value>* pChild = (pLeft != nullptr) ? pLeft : pRight;
    if (pChild) {
      pChild->setParent(pParent);
    }
    if (pParent == nullptr) {
      setRoot(pChild);
    } else if (pParent->getLeft() == p) {
      pParent->setLeft(pChild);
    } else {
      pParent->setRight(pChild);
    }

    // Delete p once pointers have been reattached.
    delete p;

    // Rebalance starting from p.
    p = pParent;
  } else {
    // Get p's successor.
    AVLNode<Key, Value>* pSuccessor = p->getRight();
    while (pSuccessor->getLeft() != nullptr) {
      pSuccessor = pSuccessor->getLeft();
    }

    // Set pSuccessor's parent's left to pSuccessor's right child.
    AVLNode<Key, Value>* pSuccessorParent = pSuccessor->getParent();
    if (pSuccessor != pRight) {
      AVLNode<Key, Value>* pSuccessorRight = pSuccessor->getRight();
      pSuccessorParent->setLeft(pSuccessorRight);
      if (pSuccessorRight != nullptr) {
        pSuccessorRight->setParent(pSuccessorParent);
      }
      pSuccessor->setRight(pRight);
      pRight->setParent(pSuccessor);
    }

    // Replace p with pSuccessor.
    pSuccessor->setParent(pParent);
    pSuccessor->setLeft(pLeft);
    if (pLeft != nullptr) {
      pLeft->setParent(pSuccessor);
    }
    if (pParent == nullptr) {
      setRoot(pSuccessor);
    } else if (pParent->getLeft() == p) {
      pParent->setLeft(pSuccessor);
    } else {
      pParent->setRight(pSuccessor);
    }

    // Delete p once pointers have been reattached.
    delete p;

    // Rebalance starting from the parent of the successor node.
    p = (pSuccessorParent == p) ? pSuccessor : pSuccessorParent;
  }

  // Fix the heights and rotate the imbalanced ancestors.
  for (; p != nullptr; p = p->getParent()) {
    p->fixHeight();
    if (p->getBalance() == 2) {
      // The right side is deeper than the left so rotate left. But rotate right
      // the right subtree to bring up it's left subtree if needed.
      if (p->getRight()->getBalance() < 0) {
        rotateRight(p->getRight());
      }
      p = rotateLeft(p);
    } else if (p->getBalance() == -2) {
      // The left side is deeper than the right so rotate right. But rotate left
      // the left subtree to bring up it's right subtree if needed.
      if (p->getLeft()->getBalance() > 0) {
        rotateLeft(p->getLeft());
      }
      p = rotateRight(p);
    }
  }
}

// Add a print which prints the keys and heights for debugging.
template <typename Key, typename Value>
void AVLTree<Key, Value>::printHeights() {
  printRootHeights(getRoot());
  std::cout << std::endl;
  validateTree();
}

// Print method to print key and level.
template <typename Key, typename Value>
void AVLTree<Key, Value>::printRootHeights(AVLNode<Key, Value>* root) {
  if (root != nullptr) {
    std::cout << "[";
    printRootHeights(root->getLeft());
    std::cout << " (" << root->getKey() << " - " << root->getHeight() << ") ";
    printRootHeights(root->getRight());
    std::cout << "]";
  }
}

// Check all the pointers and heights for the avl tree.
template <typename Key, typename Value>
void AVLTree<Key, Value>::validateTree() {
  validateSubtree(getRoot());
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::validateSubtree(AVLNode<Key, Value>* p) {
  if (p == nullptr) {
    return;
  }

  // If p's parent is null then p should be the root.
  if (p->getParent() == nullptr && AVLTree<Key, Value>::root_ != p) {
    std::cout << "Bad root pointer " << p->getKey() << std::endl;
    return;
  }

  // Check that height is one more than max child's height.
  if (p->getHeight() != std::max(p->getLeftHeight(), p->getRightHeight()) + 1) {
    std::cout << "Bad height " << p->getKey() << std::endl;
    return;
  }

  // Check the AVL balance.
  if (p->getBalance() < -1 || p->getBalance() > 1) {
    std::cout << "Bad balance " << p->getKey() << std::endl;
    return;
  }

  // Check that p is the parent of its children.
  if (p->getLeft() != nullptr) {
    if (p->getLeft()->getParent() != p) {
      std::cout << "Bad left pointer " << p->getLeft()->getKey() << std::endl;
      return;
    }
    if (p->getKey() < p->getLeft()->getKey()) {
      std::cout << "Bad left key " << p->getLeft()->getKey() << std::endl;
      return;
    }
    validateSubtree(p->getLeft());
  }
  if (p->getRight() != nullptr) {
    if (p->getRight()->getParent() != p) {
      std::cout << "Bad right pointer " << p->getRight()->getKey() << std::endl;
      return;
    }
    if (p->getKey() > p->getRight()->getKey()) {
      std::cout << "Bad right key " << p->getRight()->getKey() << std::endl;
      return;
    }
    validateSubtree(p->getRight());
  }
}

/*
 ------------------------------------------
 End implementations for the AVLTree class.
 ------------------------------------------
*/

#endif