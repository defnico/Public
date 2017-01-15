#ifndef _S16_VECTOR_H__
#define _S16_VECTOR_H__
#include <cstddef>

template <typename T> class vector {
public:
  vector();
  ~vector();
  void push_back(T n);
  void pop_back();
  vector(vector<T> &v);

  T &operator[](int i);
  int size() { return size_; }
  int capacity() { return capacity_; }
  T &back() { return data_[size_ - 1]; }

  bool empty() { return size_ == 0; }

  void resize(int n);

private:
  T *data_;
  int size_;     // Current length
  int capacity_; // Number of elements allocated
};

template <typename T> void vector<T>::resize(int n) {
  if (n <= capacity_) {
    size_ = n;
  } else {
    T *data = new T[n];
    for (int i = 0; i < size_; i++) {
      data[i] = data_[i];
    }
    delete[] data_;
    data_ = data;
    size_ = n;
    capacity_ = size_;
  }
}

template <typename T> vector<T>::vector(vector<T> &v) {
  size_ = v.size();
  capacity_ = v.capacity();
  if (v.data_ == nullptr) {
    data_ = nullptr;
  } else {
    data_ = new T[capacity_];
    for (int i = 0; i < size_; i++) {
      data_[i] = v[i];
    }
  }
}

template <typename T> vector<T>::vector() {
  data_ = NULL;
  size_ = 0;
  capacity_ = 0;
}

template <typename T> vector<T>::~vector() { delete[] data_; }

template <typename T> T &vector<T>::operator[](int i) { return data_[i]; }

template <typename T> void vector<T>::push_back(T n) {
  if (!data_) {
    data_ = new T[1];
    capacity_ = 1;
  } else if (size_ == capacity_) {
    // Add room for a new element by adding the reserve
    capacity_ *= 2;
    T *new_data = new T[capacity_];
    // Copy the old data to the new data
    for (int i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
  }
  data_[size_] = n;
  size_++;
}

template <typename T> void vector<T>::pop_back() {
  size_--;
  // delete data_[size_];
}

#endif // _S16_VECTOR_H__