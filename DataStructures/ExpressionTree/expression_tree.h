#ifndef _S16_EXPRESSION_TREE_H__
#define _S16_EXPRESSION_TREE_H__

#include <string>

class ExpressionTree {
public:
  // Throws invalid argument for invlaid rpn string
  ExpressionTree(const std::string& rpn);

  std::string rpn() const;
  std::string infix() const;

  // Returns value of expression tree,
  // throws out of range and overflow exceptions
  double eval() const;

  struct Node {
    virtual double eval() const = 0;
    virtual std::string rpn() const = 0;
    virtual std::string infix() const = 0;
    virtual std::string symbol() const = 0;
  };

private:
  Node* root_;
};

#endif // _S16_EXPRESSION_TREE_H__
