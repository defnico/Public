#include "../test/logging.h"
#include "sort.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

void print(vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}

void BubbleSortTest() {
  int data[] = {5, 3, 4, 6};
  int sorted_data[] = {3, 4, 5, 6};
  vector<int> v(data, data + sizeof(data) / sizeof(int));
  BubbleSort(v);
  for (int i = 0; i < v.size(); i++) {
    CHECK_EQ(v[i], sorted_data[i]);
  }
}

void SelectionSortTest() {
  int data[] = {7, 2, 8, 9};
  int sorted_data[] = {2, 7, 8, 9};
  vector<int> v(data, data + sizeof(data) / sizeof(int));
  SelectionSort(v);
  for (int i = 0; i < v.size(); i++) {
    CHECK_EQ(v[i], sorted_data[i]);
  }
}

void InsertionSortTest() {
  int data[] = {4, 1, 6, 3};
  int sorted_data[] = {1, 3, 4, 6};
  vector<int> v(data, data + sizeof(data) / sizeof(int));
  InsertionSort(v);
  for (int i = 0; i < v.size(); i++) {
    CHECK_EQ(v[i], sorted_data[i]);
  }
}

void MergeSortTest() {
  int data[] = {38,27,43,3,9,82,10};
  int sorted_data[] = {3,9,10,27,38,43,82};
  vector<int> v(data, data + sizeof(data) / sizeof(int));
  MergeSort(v);
  for (int i = 0; i < v.size(); i++) {
    CHECK_EQ(v[i], sorted_data[i]);
  }
}

void QuicksortTest() {
  int data[] = {34,22,49,4,8,85,11};
  int sorted_data[] = {4,8,11,22,34,49,85};
  vector<int> v(data, data + sizeof(data) / sizeof(int));
  Quicksort(v);
  for (int i = 0; i < v.size(); i++) {
    CHECK_EQ(v[i], sorted_data[i]);
  }
}

int main() {
  BEGIN_TESTS();

  BubbleSortTest();
  SelectionSortTest();
  InsertionSortTest();
  MergeSortTest();
  QuicksortTest();

}