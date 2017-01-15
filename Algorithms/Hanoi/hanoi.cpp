#include "../structs/vector.h"
#include <iostream>
using namespace std;

struct Hanoi {
  Hanoi(int n);
  void print();
  void move_tower(int disk, vector<int>& source, vector<int>& dest,
                  vector<int>& spare) {
    if (disk == 0) {
      source.pop_back();
      dest.push_back(0);
      num_moves++;
    } else {
      move_tower(disk - 1, source, spare, dest);
      source.pop_back();
      dest.push_back(disk);
      num_moves++;
      move_tower(disk - 1, spare, dest, source);
    }
  }

  vector<int> a;
  vector<int> b;
  vector<int> c;

  void Run() {
    num_moves = 0;
    move_tower(size, a, b, c);
  }

  int size;
  int num_moves;
};

Hanoi::Hanoi(int n) {
  size = n;
  for (int i = size; i >= 0; i--) {
    a.push_back(i);
  }
}

void Hanoi::print() {
  //cout << "inside function" << endl;
  vector<int> a_cp(a);
  vector<int> b_cp(b);
  vector<int> c_cp(c);
  while (a_cp.size() < size + 1) { a_cp.push_back(-1); }
  while (b_cp.size() < size + 1) { b_cp.push_back(-1); }
  while (c_cp.size() < size + 1) { c_cp.push_back(-1); }

  // cout << "a_cp size = " << a_cp.size() << endl;
  // cout << "b_cp size = " << b_cp.size() << endl;
  // cout << "c_cp size = " << c_cp.size() << endl;

  // cout << "a_cp capacity = " << a_cp.capacity() << endl;
  // cout << "b_cp capacity = " << b_cp.capacity() << endl;
  // cout << "c_cp capacity = " << c_cp.capacity() << endl;

  // for (int i = 0; i < 6; i++) {
  //   cout << a_cp[i] << " ";
  // }
  // cout << endl;
  // for (int i = 0; i < 6; i++) {
  //   cout << b_cp[i] << " ";
  // }
  // cout << endl;
  // for (int i = 0; i < 6; i++) {
  //   cout << c_cp[i] << " ";
  // }
  // cout << endl;

  // cout << "check" << endl;

  for (int i = size; i >= 0; i--) {
    if (a_cp[i] != -1) { 
      cout << "  " << a_cp[i] << "  ";
    } else {
      cout << "   ";
    }
    if (b_cp[i] != -1) { 
      cout << "   " << b_cp[i] << "  ";
    } else {
      cout << "   ";
    }
    if (c_cp[i] != -1) { 
      cout << "   " << c_cp[i] << "  ";
    } else {
      cout << "   ";
    }
    cout << endl;
  }
  cout << "--- " << " --- " << " ---" << endl;
  cout << " A " << "   B  " << "  C " << endl;
  
}

int main() {
  const int n = 5;
  Hanoi h(n);
  //h.print();
  h.Run();
  h.print();
  cout << "Number of moves = " << h.num_moves << endl;
}