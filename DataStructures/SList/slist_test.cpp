#include "../test/logging.h"
#include "slist.h"
#include <cstddef>

#include <iostream>
using namespace std;

int main() {
  BEGIN_TESTS();

  slist<int> l1;
  CHECK_EQ(l1.size(), 0);
  CHECK_EQ(l1.head(), static_cast<slist<int>::Node *>(nullptr));
  l1.push_front(4);
  CHECK_EQ(l1.size(), 1);
  CHECK_EQ(l1.head()->value, 4);
  CHECK_EQ(l1.tail(), l1.head());
  l1.push_back(7);
  CHECK_EQ(l1.tail()->value, 7);
  l1.pop_back();
  CHECK_EQ(l1.tail()->value, 4);
  l1.push_back(8);
  l1.pop_front();
  CHECK_EQ(l1.tail()->value, 8);
  l1.pop_back();

  slist<int> lr;
  lr.push_back(3);
  lr.push_back(4);
  lr.push_back(6);
  lr.push_back(7);
  lr.print();
  cout << "Sum = " << lr.sum() << endl;
  lr.print_backwards();

  slist<int> rm;
  rm.push_back(10);
  rm.push_back(6);
  rm.push_back(7);
  rm.push_back(6);
  rm.push_back(4);
  rm.print();
  rm.remove_all(6);
  rm.print();
}