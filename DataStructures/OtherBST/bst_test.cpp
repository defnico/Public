#include "../test/logging.h"
#include "bst.h"
#include <cstddef>

#include <iostream>
using namespace std;

int main() {
  BEGIN_TESTS();

  // BST<string> bst;
  // bst.insert("car");
  // bst.insert("ford");
  // bst.insert("gmc");
  // cout << bst.dot() << endl;

  BST<int> bst_num;
  bst_num.insert(50);
  cout << bst_num.dot() << endl;
  bst_num.insert(20);
  cout << bst_num.dot() << endl;
  bst_num.insert(60);
  cout << bst_num.dot() << endl;
  bst_num.insert(10);
  cout << bst_num.dot() << endl;
  bst_num.insert(30);
  cout << bst_num.dot() << endl;
  bst_num.insert(25);
  cout << bst_num.dot() << endl;
  CHECK_EQ(true, bst_num.find(50));
  CHECK_EQ(false, bst_num.find(55));
  bst_num.remove(50);
  bst_num.remove(60);
  cout << bst_num.dot() << endl;
}