#include <iostream>
using namespace std;

int main() {
  cout << "Enter a number: ";
  int num;
  cin >> num;
  int length = 0;
  while (num != 1) {
    if (num % 2 == 0) {
      num /= 2;
      length++;
      cout << num << " ";
    } else {
      num *= 3;
      num++;
      length++;
      cout << num << " ";
    }
  }
  cout << endl;
  cout << "Length: " << length << endl;
  return 0;
}