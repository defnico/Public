#include "stackstring.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

bool IsBlankLine(const string& s) {
  if (s.empty()) {
    return true;
  }

  for (size_t i = 0; i < s.size(); i++) {
    if (!std::isspace(s[i])) {
      return false;
    }
  }
  return true;
}

bool ShiftToken(string& tok, StackString& stack) {
  // Modify token by < or > if on the stack.
  while (!stack.empty()) {
    if (stack.top() == "<") {
      if (tok.size() == 1) {
        return false;
      }
      tok = tok.substr(0, tok.size() - 1);
      stack.pop();
    } else if (stack.top() == ">") {
      if (tok.size() == 1) {
        return false;
      }
      tok = tok.substr(1);
      stack.pop();
    } else {
      break;
    }
  }
  return true;
}

bool EvaluateParenthesis(string& tok, StackString& stack, int pos) {
  if (stack.empty()) {
    return false;
  }
  tok = stack.top();
  stack.pop();
  int num_operations = 0;
  while (!stack.empty() && stack.top() != "(") {
    string op = stack.top();
    num_operations++;
    stack.pop();

    if (stack.empty() || stack.top() == "(") {
      return false;
    }

    string lhs = stack.top();
    stack.pop();
    if (op == "+") {
      tok = lhs + tok;
    } else if (op == "-") {
      if (num_operations > 1) {
        return false;
      }
      size_t index = lhs.find(tok);
      if (index != string::npos) {
        tok = lhs.substr(0, index) + lhs.substr(index + tok.size());
      } else {
        tok = lhs;
      }
    } else {
      return false;
    }
  }

  if (stack.empty() || stack.top() != "(") {
    return false;
  }
  stack.pop();
  if (!ShiftToken(tok, stack)) {
    return false;
  }
  return true;
}

// The value is the result of evaluating line.
// Returns true if successful, false if malformed expression.
bool ProcessLine(const string& line, string& value) {
  StackString stack;
  for (size_t i = 0; i < line.size(); i++) {
    char c = line[i];
    if (std::isspace(c)) {
    } else if (c == '(' || c == '<' || c == '>' || c == '+' || c == '-') {
      stack.push(string(1, c));
    } else if (islower(c)) {
      string tok = string(1, c);
      while (i + 1 < line.size() && islower(line[i + 1])) {
        tok += line[i + 1];
        i++;
      }
      if (!ShiftToken(tok, stack)) {
        return false;
      }
      stack.push(tok);
    } else if (c == ')') {
      string tok;
      if (!EvaluateParenthesis(tok, stack, i)) {
        return false;
      }
      stack.push(tok);
    } else if (isupper(c)) {
      return false;
    } else {
      return false;
    }
  }

  // The top of the stack is the value of the expression.
  if (stack.empty()) {
    return false;
  }
  value = stack.top();
  stack.pop();
  if (!stack.empty()) {
    return false;
  } else if (!value.empty() && !islower(value[0])) {
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Usage: stringparser <input_file> <output_file>" << endl;
    return -1;
  }

  ifstream ifile(argv[1]);
  ofstream ofile(argv[2]);
  string line;
  while (getline(ifile, line)) {
    // if input line is empty then output a blank line.
    if (IsBlankLine(line)) {
      ofile << endl;
    } else {
      string value;
      if (!ProcessLine(line, value)) {
        ofile << "Malformed" << endl;
      } else {
        ofile << value << endl;
      }
    }
  }
}
