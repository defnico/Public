#include "avlbst.h"
#include "building.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Technically this is not needed for the assignment, but it is usually good
// practice to test the inputs
bool IsValidColor(string color) {
  if (color.size() > 20) {
    return false;
  }
  for (size_t i = 0; i < color.size(); i++) {
    if (!islower(color[i])) {
      return false;
    }
  }
  return true;
}

void OutputError(ofstream& output, string s) {
  output << "Error - incorrect command" << endl;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  const long long MaxHeight = 9223372036854775807LL; // 2^63 - 1

  // Construct the building.
  Building building(MaxHeight);

  string line;
  while (getline(input, line)) {
    istringstream ss(line);
    string command;
    ss >> command;
    if (command == "RECOLOR") {
      long long start, end;
      string color;
      ss >> start >> end >> color;
      bool badInput = ss.fail();
      bool validColor = IsValidColor(color);
      string lastWord;
      ss >> lastWord;
      bool extraData = !ss.fail();
      if (badInput || !validColor || extraData || end < 1 || start < 1 ||
          end < start) {
        OutputError(output, line);
      } else {
        building.Recolor(start, end, color);
      }
    } else if (command == "COLOR") {
      long long floor;
      ss >> floor;
      bool badInput = ss.fail();
      string lastWord;
      ss >> lastWord;
      bool extraData = !ss.fail();
      if (badInput || extraData || floor < 1) {
        OutputError(output, line);
      } else {
        string color = building.GetColor(floor);
        output << color << endl;
      }
    } else {
      OutputError(output, line);
    }
  }
  return 0;
}
