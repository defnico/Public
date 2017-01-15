#include <iostream>
using namespace std;

int main() {
  cout << "Enter the range you want to search: ";
  int num_a, num_b;
  cin >> num_a >> num_b;
  if (num_a > num_b) {
    cout << "Invalid range" << endl;
    return 1;
  }
  int min_len = 1000;
  int min_num = 0;
  int max_len = 0;
  int max_num = 0;
  for (int i = num_a; i <= num_b; i++) {
    int num = i;
    int length = 0;
    while (num != 1) {
      if (num % 2 == 0) {
        num /= 2;
        length++;
      } else {
        num *= 3;
        num++;
        length++;
      }
    }
    if (length < min_len) {
      min_len = length;
      min_num = i;
    }
    if (length > max_len) {
      max_len = length;
      max_num = i;
    }
  }
  cout << "Minumum length: " << min_len << endl;
  cout << "Achieved by: " << min_num << endl;
  cout << "Maximum length: " << max_len << endl;
  cout << "Achieved by: " << max_num << endl;
  return 0; 
}