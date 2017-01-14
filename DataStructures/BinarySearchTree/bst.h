#ifndef BST_H_
#define BST_H_
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

struct Node {
  Node(int v, Node* p) : value(v), parent(p), left(nullptr), right(nullptr) {}
  int value;
  Node* parent;
  Node* left;
  Node* right;
};

class BST {
public:
  BST() : root_(nullptr) {}
  bool empty() { return root_ == nullptr; }
  bool insert(int v);
  bool remove(int v);
  bool find(int v);

  void print();

private:
  Node* root_;
};

bool BST::insert(int v) {
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
      } else if (v > n->value) {
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

bool BST::find(int v) {
  Node* n = root_;
  while (n != nullptr) {
    if (n->value == v) {
      return true;
    } else if (v < n->value) {
      n = n->left;
    } else if (v > n->value) {
      n = n->right;
    }
  }
  return false;
}

void printTree(Node* n) {
  if (n == nullptr) {
    return;
  } else {
    std::cout << n->value << " " << std::endl;
  }
  printTree(n->left);
  printTree(n->right);
}

void BST::print() {
  Node* n = root_;
  printTree(n);
}

#endif