#include "../test/logging.h"
#include "expression_tree.h"

#include <iostream>
using namespace std;

void TestBadRPN() {
  bool valid_arg = true;
  try {
    // Construct tree from rpn string.
    string s = "1 2 3 4 5 + +";
    ExpressionTree t(s);
    // Evaluate.
    int value = t.eval();
    cout << "t.eval(\"" << s << "\") = " << value << endl;
  } catch (invalid_argument e) {
    valid_arg = false;
    cerr << "Could not construct tree: " << e.what() << endl;
  }
  CHECK_EQ(valid_arg, false);
}

void TestDivideByZero() {
  bool underflow = false;
  try {
    // Construct tree from rpn string.
    string s = "1 0 /";
    ExpressionTree t(s);
    // Evaluate.
    int value = t.eval();
    cout << "t.eval(\"" << s << "\") = " << value << endl;
  } catch (invalid_argument e) {
    cerr << "Could not construct tree: " << e.what() << endl;
  } catch (std::overflow_error e) {
    underflow = true;
    cerr << "Could not evaluate tree: " << e.what() << endl;
  }
  CHECK_EQ(underflow, true);
}

void AbsTest() {
  try {
    // Construct tree from rpn string.
    string s = "-4 abs";
    ExpressionTree t(s);
    // Evaluate.
    int value = t.eval();
    cout << "t.eval(\"" << s << "\") = " << value << endl;
    CHECK_EQ(t.eval(), 4);
  } catch (invalid_argument e) {
    cerr << "Could not construct tree: " << e.what() << endl;
  } catch (std::overflow_error e) {
    cerr << "Could not evaluate tree: " << e.what() << endl;
  }
}

void MaxTest() {
  try {
    // Construct tree from rpn string.
    string s = "2 4 max";
    ExpressionTree t(s);
    // Evaluate.
    int value = t.eval();
    cout << "t.eval(\"" << s << "\") = " << value << endl;
    CHECK_EQ(t.eval(), 4);
  } catch (invalid_argument e) {
    cerr << "Could not construct tree: " << e.what() << endl;
  } catch (std::overflow_error e) {
    cerr << "Could not evaluate tree: " << e.what() << endl;
  }
}

void MinTest() {
  try {
    // Construct tree from rpn string.
    string s = "-2 10 min";
    ExpressionTree t(s);
    // Evaluate.
    int value = t.eval();
    cout << "t.eval(\"" << s << "\") = " << value << endl;
    CHECK_EQ(t.eval(), -2);
  } catch (invalid_argument e) {
    cerr << "Could not construct tree: " << e.what() << endl;
  } catch (std::overflow_error e) {
    cerr << "Could not evaluate tree: " << e.what() << endl;
  }
}

void PowTest() {
  try {
    // Construct tree from rpn string.
    string s = "2 3 ^";
    ExpressionTree t(s);
    // Evaluate.
    int value = t.eval();
    cout << "t.eval(\"" << s << "\") = " << value << endl;
    CHECK_EQ(t.eval(), 8);
  } catch (invalid_argument e) {
    cerr << "Could not construct tree: " << e.what() << endl;
  } catch (std::overflow_error e) {
    cerr << "Could not evaluate tree: " << e.what() << endl;
  }
}

void FactTest() {
  try {
    // Construct tree from rpn string.
    string s = "5 !";
    ExpressionTree t(s);
    // Evaluate.
    int value = t.eval();
    cout << "t.eval(\"" << s << "\") = " << value << endl;
    CHECK_EQ(t.eval(), 120);
  } catch (invalid_argument e) {
    cerr << "Could not construct tree: " << e.what() << endl;
  } catch (std::overflow_error e) {
    cerr << "Could not evaluate tree: " << e.what() << endl;
  }
}

int main() {
  BEGIN_TESTS();

  TestBadRPN();
  TestDivideByZero();
  AbsTest();
  MaxTest();
  PowTest();
  MinTest();
  FactTest();

  // string s = "3 4 +";
  // ExpressionTree t(s);
  // cout << t.rpn() << endl;
  // cout << t.infix() << endl;
  // cout << t.eval() << endl;
}
