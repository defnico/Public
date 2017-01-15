#include "../test/logging.h"
#include "vector.h"

int main() {
  vector<int> v;
  CHECK_EQ(v.size(), 0);
  v.push_back(2);
  CHECK_EQ(v.size(), 1);
  CHECK_EQ(v[0], 2);
  v[0] = 7;
  CHECK_EQ(v[0], 7);
  v.push_back(4);
  CHECK_EQ(v.size(), 2);
  CHECK_EQ(v.back(), 4);
  v.pop_back();
  CHECK_EQ(v.size(), 1);
  CHECK_GE(v.capacity(), 2);
  v.pop_back();
  CHECK_EQ(v.size(), 0);

  vector<int> a;
  a.push_back(4);
  a.push_back(6);
  a.push_back(7);
  a.push_back(8);
  std::cout << a.size() << std::endl;
  std::cout << a.capacity() << std::endl;
  a.resize(8);
  std::cout << a.capacity() << std::endl;
}