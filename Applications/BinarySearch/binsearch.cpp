#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

void sort(int *, int);
int binsearch(int, int *, int, int);
void sort_recursive(int* , int);

int main(int argc, char *argv[]){
  int target;
  if(argc < 2) {
    cout << "Provide a filename of the data to be searched" << endl;
    return 1;
  }
  ifstream datfile(argv[1], ios::in);
  if( datfile.fail() ){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }
  int count = 0;
  // Count how many integers are in the file
  while(!datfile.fail()){
    int temp;
    datfile >> temp;
    if(!datfile.fail()){
      count++;
    }
  }
  // When we reach the end of the file, the EOF flag is set
  // To be able to read through the file again we need to clear that flag
  datfile.clear();
  //  We also need to set our internal position in the file back to 0
  datfile.seekg(0,ios::beg);

  // Now allocate an array to store the file data and read in the data
  int *data = new int[count];
  for(int i=0; i < count; i++){
    datfile >> data[i];
  }

  datfile.close();

  cout << "Read " << count << " integers from the data file.\n";
  cout << "Enter the target positive integer to search for: ";
  cin >> target;

  // cout << "Testing max_idx" << endl;
  // cout << max_index(data, count) << endl;

  // Uncomment the line below for part 2
  cout << "Selection Sort" << endl;
  sort(data, count);

  cout << "Recursive Selection Sort" << endl;
  sort_recursive(data, count);
  for (int i = 0; i < count; i++) {
    cout << data[i] << " ";
  }
  cout << endl;

  // Call binary search
  int retval = binsearch(target,data,0,count);

  // Interpret and print the results
  if (retval == -1){
    cout << target << " does not appear in the data." << endl;
  } else {
    cout << target << " appears at index " << retval << " in the data." << endl;
  }

  // Deallocate the data array
  delete[] data;
  return 0;
}

// Returns the index in the data array where target is located
//  or -1 if the target value is not in the list
int binsearch(int target, int *data, int start, int end) {
  if (start > end) {
    return -1;
  }
  int middle = (start + end) / 2;
  if (target == data[middle]) {
    return middle;
  } else if (target < data[middle]) {
    return binsearch(target, data, start, middle-1);
  } else {
    return binsearch(target, data, middle+1, end);
  }
  return -1;
}

// implements a selection sort algorithm to sort
//  the integer values in the 'data' array of size 'len'
// You aren't allowed to change the prototype of this function
void sort(int* data, int len) {
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (data[j] < data[i]) {
        swap(data[i], data[j]);
      }
    }
    cout << data[i] << " ";
  }
  cout << endl;
}

void sort_recursive(int* data, int len) {
  if (len == 0) {
    return;
  } else {
    for (int i = 1; i < len; i++) {
      if (data[i] < data[0]) {
        swap(data[i], data[0]);
      }
    }
    sort_recursive(data + 1, len - 1);
  }
}
