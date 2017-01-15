#include "../test/logging.h"
#include "queue.h"
#include <cstddef>

#include <iostream>
using namespace std;

int main() {
  BEGIN_TESTS();

  queue<string> q;
  CHECK_EQ(q.empty(), true);
  q.push("Nico");
  CHECK_EQ(q.front(), "Nico");
  q.push("Daniel");
  q.push("Kevin");
  CHECK_EQ(q.empty(), false);
  q.pop();
  CHECK_EQ(q.front(), "Daniel");
  q.pop();

  queue<string> s;
  CHECK_EQ(s.empty(), true);
  s.push("Daniel");
  CHECK_EQ(s.front(), "Daniel");
  s.push("Kevin");
  CHECK_EQ(s.front(), "Daniel");
  s.push("Nico");
  CHECK_EQ(s.front(), "Daniel");

  CHECK_EQ(s.front(), "Daniel");
  s.pop();
  CHECK_EQ(s.front(), "Kevin");
  s.pop();
  CHECK_EQ(s.front(), "Nico");
  s.pop();
}