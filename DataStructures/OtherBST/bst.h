#ifndef _S16_BST_H__
#define _S16_BST_H__
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

template <typename T> class BST {
public:
  BST() : root_(nullptr) {}
  bool empty() const { return root_ == nullptr; }
  bool insert(const T& v);     // Returns true if successfully inserted
  bool remove(const T& v);     // Returns true if successfully removed
  bool find(const T& v) const; // Returns true if found

  std::string dot() const; // Create string to feed to webgraphviz.com

  struct Node {
    Node(T v, Node* p) : value(v), parent(p), left(nullptr), right(nullptr) {}
    T value;
    Node* parent;
    Node* left;
    Node* right;

    std::string dot() const;
  };

private:
  Node* root_;
};

template <typename T> bool BST<T>::insert(const T& v) {
  if (empty()) {
    root_ = new Node(v, nullptr);
    return true;
  } else {
    Node* n = root_;
    while (true) {
      if (v == n->value) {
        return false;
      } else if (v < n->value) {
        if (n->left == nullptr) {
          n->left = new Node(v, n);
          return true;
        } else {
          n = n->left;
        }
      } else {
        if (n->right == nullptr) {
          n->right = new Node(v, n);
          return true;
        } else {
          n = n->right;
        }
      }
    }
  }
}

template <typename T> bool BST<T>::find(const T& v) const {
  const Node* n = root_;
  while (n != nullptr) {
    if (v == n->value) {
      return true;
    } else if (v < n->value) {
      n = n->left;
    } else {
      n = n->right;
    }
  }
  return false;
}

template <typename T> bool BST<T>::remove(const T& v) {
  Node* n = root_;
  while (n != nullptr) {
    if (n->value == v) {
      break;
    } else if (v < n->value) {
      n = n->left;
    } else {
      n = n->right;
    }
  }

  if (n == nullptr) { // v not found in the tree.
    return false;
  } else if (n->left == nullptr && n->right == nullptr) { // Remove leaf.
    Node* parent = n->parent;
    if (parent == nullptr) {
      root_ = nullptr; // root is a leaf.
    } else {
      if (parent->left == n) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    }
    delete n;
  } else if (n->left != nullptr) { // Move the largest of the smallest.
    Node* m = n->left;
    while (m->right != nullptr) { // Go to the max right node.
      m = m->right;
    }

    n->value = m->value; // Copy largest of smallest value to deleted value.
    if (m->parent->left == m) {
      m->parent->left = m->left;
    } else {
      m->parent->right = m->left;
    }
    delete m;
  } else { // Move the smallest of the largest.
    Node* m = n->right;
    while (m->left != nullptr) { // Go to the max right node.
      m = m->left;
    }

    n->value = m->value; // Copy leaf value to deleted value.
    if (m->parent->left == m) {
      m->parent->left = m->right;
    } else {
      m->parent->right = m->right;
    }
    delete m;
  }

  return true;
}

template <typename T> std::string BST<T>::Node::dot() const {
  std::string s;
  if (left == nullptr && right == nullptr) {
    return s;
  }

  std::ostringstream ss;
  ss << value;
  const std::string& str = ss.str();

  if (left != nullptr) {
    std::ostringstream ssl;
    ssl << left->value;
    s += " " + str + " -- " + ssl.str() + "\n";
  } else {
    s += " " + str + " -- l_" + ss.str() + "\n";
  }
  if (right != nullptr) {
    std::ostringstream ssr;
    ssr << right->value;
    s += " " + str + " -- " + ssr.str() + "\n";
  } else {
    s += " " + str + " -- r_" + ss.str() + "\n";
  }
  if (left != nullptr) {
    s += left->dot();
  }
  if (right != nullptr) {
    s += right->dot();
  }
  return s;
}

template <typename T> std::string BST<T>::dot() const {
  std::string s = "graph {\n";
  if (root_ != nullptr) {
    s += root_->dot();
  }
  s += "}";
  return s;
}

#endif //_S16_BST_H__