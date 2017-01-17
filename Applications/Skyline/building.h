#ifndef BUILDING_H
#define BUILDING_H

#include "avlbst.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

struct FloorRange {
  FloorRange(long long s, long long e) : start(s), end(e) {}
  long long start;
  long long end;

  // Two FloorRange's are equal if there is any overlap.
  bool operator==(const FloorRange& other) const {
    if (end < other.start || start > other.end) {
      return false;
    } else {
      return true;
    }
  }
  bool operator<(const FloorRange& other) const { return end < other.start; }
  bool operator>(const FloorRange& other) const { return start > other.end; }
};

inline std::ostream& operator<<(std::ostream& os, const FloorRange& range) {
  os << '{' << range.start << ", " << range.end << '}';
  return os;
}

class Building {
public:
  // Construct the building with numFloors. Initially colored all white.
  Building(long long numFloors);

  // Return the color for the given floor.
  std::string GetColor(long long floor);

  // Set the color of floors start to end (inclusive) to the given color.
  void Recolor(long long start, long long end, std::string color);

  // Print the AVL tree.
  void DebugPrint() { floorColors_.printHeights(); }

  // Print the floor intervals with their colors.
  void Print();

private:
  AVLTree<FloorRange, std::string> floorColors_;
};

#endif
