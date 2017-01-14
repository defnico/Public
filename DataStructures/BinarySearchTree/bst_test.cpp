#include "bst.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace std;

TEST(BstTest, Basic) {
  BST bst;
  EXPECT_EQ(true, bst.empty());
  bst.insert(8);
  bst.insert(3);
  bst.insert(1);
  bst.insert(6);
  bst.insert(4);
  bst.insert(7);
  bst.insert(10);
  bst.insert(13);
  bst.insert(16);
  EXPECT_EQ(false, bst.find(20));
  EXPECT_EQ(true, bst.find(8));
  EXPECT_EQ(true, bst.find(3));
  EXPECT_EQ(true, bst.find(1));
  EXPECT_EQ(true, bst.find(6));
  EXPECT_EQ(true, bst.find(4));
  EXPECT_EQ(true, bst.find(7));
  EXPECT_EQ(true, bst.find(10));
  EXPECT_EQ(true, bst.find(13));
  EXPECT_EQ(true, bst.find(16));
  EXPECT_EQ(false, bst.find(22));
  bst.print();
}