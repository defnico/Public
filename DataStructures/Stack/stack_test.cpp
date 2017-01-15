#include "../test/logging.h"
#include "slist.h"
#include "stack.h"
#include <cstddef>

#include <iostream>
using namespace std;

template <typename T> void reverse_print(slist<T> &list) {
  stack<T> s;
  typename slist<T>::Node *n = list.head();
  while (n != nullptr) {
    s.push(n->value);
    n = n->next;
  }
  while (!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
}

int main() {
  BEGIN_TESTS();

  stack<int> s;
  CHECK_EQ(s.empty(), true);
  s.push(4);
  CHECK_EQ(s.top(), 4);
  s.push(7);
  CHECK_EQ(s.empty(), false);
  s.pop();
  CHECK_EQ(s.top(), 4);

  slist<string> words;
  words.push_back("Nico");
  words.push_back("Kevin");
  words.push_back("Daniel");
  reverse_print(words);
}