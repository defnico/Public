#include "expression_tree.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stack>
using namespace std;

typedef ExpressionTree::Node Node;

string ExpressionTree::rpn() const { return root_->rpn(); }
string ExpressionTree::infix() const { return root_->infix(); }
double ExpressionTree::eval() const { return root_->eval(); }

struct Number : public Node {
  Number(double num) : number(num) {}
  double eval() const { return number; }
  string rpn() const {
    ostringstream nums;
    nums << number;
    return nums.str();
  }
  string infix() const { return rpn(); }
  string symbol() const { return rpn(); }
  double number;
};

struct BinaryFunc : public Node {
  BinaryFunc(Node* l, Node* r) : left(l), right(r) {}
  string rpn() const { return left->rpn() + " " + right->rpn() + " " + symbol(); }
  virtual string infix() const {
    return symbol() + "(" + left->infix() + ", " + right->infix() + ")";
  }
  Node* left;
  Node* right;
};
struct BinaryOp : public BinaryFunc {
  BinaryOp(Node* l, Node* r) : BinaryFunc(l, r) {}
  string infix() const {
    return "(" + left->infix() + " " + symbol() + " " + right->infix() + ")";
  }
};

struct AddOp : public BinaryOp {
  AddOp(Node* l, Node* r) : BinaryOp(l, r) {}
  string symbol() const { return "+"; }
  double eval() const { return left->eval() + right->eval(); }
};
struct SubtractOp : public BinaryOp {
  SubtractOp(Node* l, Node* r) : BinaryOp(l, r) {}
  string symbol() const { return "-"; }
  double eval() const { return left->eval() - right->eval(); }
};
struct MultiplyOp : public BinaryOp {
  MultiplyOp(Node* l, Node* r) : BinaryOp(l, r) {}
  string symbol() const { return "*"; }
  double eval() const { return left->eval() * right->eval(); }
};
struct DivideOp : public BinaryOp {
  DivideOp(Node* l, Node* r) : BinaryOp(l, r) {}
  string symbol() const { return "/"; }
  double eval() const {
    double denom = right->eval();
    if (denom == 0) {
      throw overflow_error("Divide by zero.");
    } else {
      return left->eval() / denom;
    }
  }
};

struct Max : public BinaryFunc {
  Max(Node* a1, Node* a2) : BinaryFunc(a1, a2) {}
  string symbol() const { return "max"; }
  double eval() const { return std::max(left->eval(), right->eval()); }
};
struct Min : public BinaryFunc {
  Min(Node* a1, Node* a2) : BinaryFunc(a1, a2) {}
  string symbol() const { return "min"; }
  double eval() const { return std::min(left->eval(), right->eval()); }
};
struct Pow : public BinaryFunc {
  Pow(Node* a1, Node* a2) : BinaryFunc(a1, a2) {}
  string symbol() const { return "^"; }
  double eval() const { return std::pow(left->eval(), right->eval()); }
};

struct UnaryFunc : public Node {
  UnaryFunc(Node* a) : arg(a) {}
  string rpn() const { return arg->rpn() + " " + symbol(); }
  virtual string infix() const { return symbol() + "(" + arg->infix() + ")"; }
  Node* arg;
};
struct Abs : public UnaryFunc {
  Abs(Node* n) : UnaryFunc(n) {}
  double eval() const { return std::abs(arg->eval()); }
  string symbol() const { return "abs"; }
};
struct Fact : public UnaryFunc {
  Fact(Node* n) : UnaryFunc(n) {}
  int factorial(int n) const {
    if (n == 0) {
      return 1;
    } else {
      return n * factorial(n - 1);
    }
  }
  double eval() const { return factorial(static_cast<int>((arg->eval()))); }
  string symbol() const { return "!"; }
  string infix() const { return arg->infix() + symbol(); }
};

Node* pop_top(stack<Node*>& stk, string symbol) {
  if (stk.empty()) {
    if (symbol.empty()) {
      throw invalid_argument("bad expression");
    } else {
      throw invalid_argument("bad expression for symbol " + symbol);
    }
  }
  Node* t = stk.top();
  stk.pop();
  return t;
}

ExpressionTree::ExpressionTree(const string& s) {
  stack<Node*> stk;
  istringstream str(s);
  string symbol;
  while (str >> symbol) {
    // First see if it is a Number.
    istringstream double_str(symbol);
    double value;
    if (double_str >> value) {
      stk.push(new Number(value));
    } else if (symbol == "+") {
      Node* r = pop_top(stk, symbol);
      Node* l = pop_top(stk, symbol);
      stk.push(new AddOp(l, r));
    } else if (symbol == "-") {
      Node* r = pop_top(stk, symbol);
      Node* l = pop_top(stk, symbol);
      stk.push(new SubtractOp(l, r));
    } else if (symbol == "*") {
      Node* r = pop_top(stk, symbol);
      Node* l = pop_top(stk, symbol);
      stk.push(new MultiplyOp(l, r));
    } else if (symbol == "/") {
      Node* r = pop_top(stk, symbol);
      Node* l = pop_top(stk, symbol);
      stk.push(new DivideOp(l, r));
    } else if (symbol == "abs") {
      Node* arg = pop_top(stk, symbol);
      stk.push(new Abs(arg));
    } else if (symbol == "max") {
      Node* a1 = pop_top(stk, symbol);
      Node* a2 = pop_top(stk, symbol);
      stk.push(new Max(a1, a2));
    } else if (symbol == "min") {
      Node* a1 = pop_top(stk, symbol);
      Node* a2 = pop_top(stk, symbol);
      stk.push(new Min(a1, a2));
    } else if (symbol == "^") {
      Node* a2 = pop_top(stk, symbol);
      Node* a1 = pop_top(stk, symbol);
      stk.push(new Pow(a1, a2));
    } else if (symbol == "!") {
      Node* arg = pop_top(stk, symbol);
      stk.push(new Fact(arg));
    } else {
      throw invalid_argument("Unrecognized symbol " + symbol);
    }
  }
  root_ = pop_top(stk, "");
  if (!stk.empty()) {
    throw invalid_argument("Stack not empty.");
  }
}
