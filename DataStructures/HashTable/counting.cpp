#include "Hashtable.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cout << "[input] [output] x d r" << endl;
    return -1;
  }
  ifstream ifile(argv[1]);
  ofstream ofile(argv[2]);
  string probingTypeStr(argv[3]);
  string debugStr(argv[4]);
  string numIterationStr(argv[5]);

  unsigned int probingType = stoi(probingTypeStr);
  bool debugOn = (stoi(debugStr) == 1 ? true : false);
  int numIters = stoi(numIterationStr);

  // Preprocessing here that will not be timed.
  vector<string> words;
  string line;
  while (getline(ifile, line)) {
    stringstream ss(line);
    string word;
    while (ss >> word) {
      string tempWord;
      for (size_t i = 0; i < word.length(); i++) {
        if (isalpha(word[i])) {
          tempWord += static_cast<char>(tolower(word[i]));
        }
      }
      if (!tempWord.empty()) {
        words.push_back(tempWord);
      }
    }
  }

  // Do the word insertions one time and output the contents of the table.
  {
    Hashtable hashtable(debugOn, probingType);
    for (size_t j = 0; j < words.size(); j++) {
      hashtable.add(words[j]);
    }
    hashtable.reportAll(ofile);

    cout << endl;
    if (probingType == 0) {
      cout << "Linear probing" << endl;
    } else if (probingType == 1) {
      cout << "Quadratic probing" << endl;
    } else if (probingType == 2) {
      cout << "Double Hashing" << endl;
    } else {
      cout << "Default to double hashing" << endl;
    }
    cout << "num words = " << words.size() << endl;
    cout << "table size = " << hashtable.tableSize() << endl;
    cout << "num unique words = " << hashtable.numUniqueEntries() << endl;
  }

  // Time numIters iterations of hash table insertion.
  clock_t start = clock();
  for (int i = 0; i < numIters; i++) {
    Hashtable hashtable(debugOn, probingType);
    for (size_t j = 0; j < words.size(); j++) {
      hashtable.add(words[j]);
    }
  }

  // Report the average duration.
  double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
  cout << "Duration: " << duration / numIters << endl;
  cout << "Average operation time: "
       << (duration / numIters / words.size()) * 1000000 << endl;
}
