#include "../test/logging.h"
#include "set.h"
#include <cstddef>

#include <iostream>
using namespace std;

int main() {
  BEGIN_TESTS();

  set<int> s;
  CHECK_EQ(s.empty(), true);

  set<int>::iter i = s.begin();
  CHECK_EQ(i == s.end(), true);

  CHECK_EQ(s.find(4) == s.end(), true);

  CHECK_EQ(s.insert(4) == s.end(), false);

  CHECK_EQ(s.find(4) == s.end(), false);
  CHECK_EQ(s.insert(6) == s.end(), false);
  CHECK_EQ(s.size(), 2);

  cout << s << endl;
}