#ifndef _S16_SORT_H__
#define _S16_SORT_H__

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void BubbleSort(std::vector<T>& v) {
  for (int i = v.size()-1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (v[j] > v[i]) {
        std::swap(v[i], v[j]);
      }
    }
  }
}

template<typename T>
void SelectionSort(std::vector<T>& v) {
  for (int i = 0; i < v.size()-1; i++) {
    int min_index = i;
    for (int j = i+1; j < v.size(); j++) {
      if (v[j] < v[min_index]) {
        min_index = j;
      }
    }
    std::swap(v[min_index], v[i]);
  }
}

template<typename T>
void InsertionSort(std::vector<T>&v) {
  for (int i = 1; i < v.size(); i++) {
    int element = v[i];
    int j = i;
    while (j > 0 && v[j - 1] > element) {
      v[j] = v[j - 1];
      j = j - 1;
    }
    v[j] = element;
  }
}

template<typename T>
void print(std::vector<T>& v, int l, int r) {
  if (l <= r) {
    for (int i = l; i <= r; i++) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl;
  }
}

template<typename T>
void Merge(std::vector<T>& v, int l, int m, int r) {
  std::vector<T> left(m - l + 1);
  std::vector<T> right(r - m);
  for (int i = l; i <= m; i++) {
    left[i - l] = v[i];
  }
  for (int i = m + 1; i <= r; i++) {
    right[i - (m + 1)] = v[i];
  }
  int i = 0; // index for left
  int j = 0; // index for right
  int k = l; // v index
  while (i < left.size() && j < right.size()) {
    if (left[i] <= right[j]) {
      v[k] = left[i];
      i++;
    } else {
      v[k] = right[j];
      j++;
    }
    k++;
  }
  while (i < left.size()) {
    v[k] = left[i];
    i++;
    k++;
  }
  while (r < right.size()) {
    v[k] = right[j];
    j++;
    k++;
  }
}

template<typename T>
void MergeSortRange(std::vector<T>& v, int l, int r) {
  if (l < r) {
    // std::cout << "Before Merge: ";
    // print(v, l, r);
    int m = (l + r) / 2;
    MergeSortRange(v, l, m);
    MergeSortRange(v, m + 1, r);
    Merge(v, l, m, r);
    // std::cout << "After Merge: ";
    // print(v, l, r);
  } else if (l == r) {
    //print(v, l, r);
  }
}

template<typename T>
void MergeSort(std::vector<T>&v) {
  MergeSortRange(v, 0, v.size()-1);
}

template<typename T>
int Partition(std::vector<T>& v, int left, int right) {
  int mid = left + (right - left) / 2;
  T pivot = v[mid];
  std::swap(v[mid], v[left]);
  int i = left + 1;
  int j = right;
  while (i <= j) {
    while (i <= j && v[i] <= pivot) {
      i++;
    }
    while (i <= j && v[j] > pivot) {
      j--;
    }
    if (i < j) {
      std::swap(v[i], v[j]);
    }
  }
  std::swap(v[i - 1], v[left]);
  return i - 1;
}

template<typename T>
void QuicksortRange(std::vector<T>& v, int left, int right) {
  if (left >= right) {
    return;
  }
  int p = Partition(v, left, right);
  QuicksortRange(v, left, p - 1);
  QuicksortRange(v, p + 1, right);
}

template<typename T>
void Quicksort(std::vector<T>& v) {
  QuicksortRange(v, 0, v.size() - 1);
}

#endif // _S16_SORT_H__