#include "building.h"
#include <iostream>
#include <string>
using namespace std;

// Construct the building and initialize all the floors to white.
Building::Building(long long numFloors) {
  floorColors_.insert(
      pair<FloorRange, string>(FloorRange(1, numFloors), "white"));
}

// Return the color of the specified floor.
string Building::GetColor(long long floorNumber) {
  FloorRange key(floorNumber, floorNumber);
  AVLTree<FloorRange, string>::iterator i = floorColors_.find(key);
  if (i == floorColors_.end()) {
    return "Not a valid floor " + std::to_string(floorNumber);
  } else {
    return i->second;
  }
}

// Recolor floors insertStart to insertEnd.
void Building::Recolor(long long insertStart, long long insertEnd,
                       string color) {
  FloorRange insertRange(insertStart, insertEnd);
  AVLTree<FloorRange, string>::iterator i = floorColors_.find(insertRange);
  // Keep searching for nodes that need to be trimmed until there is no node
  // that overlaps insertRange.
  while (i != floorColors_.end()) {
    FloorRange& range = i->first;
    string& rangeColor = i->second;
    // Modify or delete the range so that there is no overlap with insert range.
    if (insertStart <= range.start && range.end <= insertEnd) {
      floorColors_.remove(range);
    } else if (insertStart <= range.start && range.start <= insertEnd &&
               range.end > insertEnd) {
      // Trim start of insert range.
      range.start = insertEnd + 1;
    } else if (insertStart <= range.end && range.end <= insertEnd &&
               range.start < insertStart) {
      // Trim end of insert range.
      range.end = insertStart - 1;
    } else if (range.start <= insertStart && insertEnd <= range.end) {
      long long saveRangeEnd = range.end;
      range.end = insertStart - 1;
      floorColors_.insert(pair<FloorRange, string>(
          FloorRange(insertEnd + 1, saveRangeEnd), rangeColor));
    }
    i = floorColors_.find(insertRange);
  }
  floorColors_.insert(pair<FloorRange, string>(insertRange, color));
}

// Print out the floor color ranges.
void Building::Print() {
  AVLTree<FloorRange, string>::iterator it;
  for (it = floorColors_.begin(); it != floorColors_.end(); ++it) {
    const FloorRange& range = it->first;
    const string& color = it->second;
    cout << "[" << range.start << " " << color << " " << range.end << "]"
         << endl;
  }
}