#include "Hashtable.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

Hashtable::Hashtable(bool debug, unsigned int probing)
    : debug_(debug), probing_(probing), numEntries_(0) {
  tableSizesIndex_ = 0;
  int tableSize = tableSizes_[tableSizesIndex_];
  table_.resize(tableSize);

  // If not in debug mode then generate 5 random numbers
  // between 0 and 1685759166. The defaults for debug mode
  // are set in the header file.
  if (!debug) {
    constexpr int n = 1685759166;
    std::srand(0);
    r1_ = static_cast<int>((std::rand() / double(RAND_MAX)) * n);
    r2_ = static_cast<int>((std::rand() / double(RAND_MAX)) * n);
    r3_ = static_cast<int>((std::rand() / double(RAND_MAX)) * n);
    r4_ = static_cast<int>((std::rand() / double(RAND_MAX)) * n);
    r5_ = static_cast<int>((std::rand() / double(RAND_MAX)) * n);
  }
}

Hashtable::~Hashtable() {}

void Hashtable::add(string key) {
  int doubleHashValue;
  int startHashKey = hash(key, doubleHashValue);
  unsigned int count = 0;
  int hashKey = startHashKey;
  while ((table_[hashKey].value != 0) && (count < table_.size())) {
    if (table_[hashKey].key == key) {
      table_[hashKey].value++;
      return;
    }
    count++;
    hashKey = probe(startHashKey, count, doubleHashValue);
  }

  // Key was not found so hashKey should be at an empty slot.
  assert(table_[hashKey].value == 0);

  // Insert at the empty slot if load factor is small enough.
  if (loadFactor() < .5) {
    table_[hashKey].key = key;
    table_[hashKey].value = 1;
  } else {
    // Resize since load factor is over threshold.
    resize();

    // Insert the key in the resized table.
    // The hashKey has to be regenerated since the table size changed.
    insertNewKeyValue(key, 1);
  }

  // numEntries was had to be updated
  numEntries_++;
}

// Insert the <key,value> in the next empty slot.
void Hashtable::insertNewKeyValue(string key, int value) {
  int doubleHashValue;
  int startHashKey = hash(key, doubleHashValue);
  unsigned int count = 0;
  int hashKey = startHashKey;
  while (table_[hashKey].value != 0 && (count < table_.size())) {
    count++;
    hashKey = probe(startHashKey, count, doubleHashValue);
  }

  assert(table_[hashKey].value == 0);

  table_[hashKey].key = key;
  table_[hashKey].value = value;
}

// Get the next hash key from a given hash key.
int Hashtable::probe(int startHashKey, int count, int doubleHashValue) const {
  int step;
  if (probing_ == 0) { // Linear probing.
    step = count;
  } else if (probing_ == 1) { // Quadratic probing.
    step = count * count;
  } else { // Double hashing.
    step = count * doubleHashValue;
  }

  return (startHashKey + step) % table_.size();
}

int Hashtable::count(string key) const {
  int doubleHashValue;
  int startHashKey = hash(key, doubleHashValue);
  unsigned int count = 0;
  int hashKey = startHashKey;
  while ((table_[hashKey].value != 0) && (count < table_.size())) {
    if (table_[hashKey].key == key) {
      return table_[hashKey].value;
    }
    count++;
    hashKey = probe(startHashKey, count, doubleHashValue);
  }

  return 0;
}

void Hashtable::reportAll(ostream& os) const {
  for (size_t i = 0; i < table_.size(); i++) {
    if (table_[i].value != 0) {
      os << table_[i].key << " " << table_[i].value << endl;
    }
  }
}

void Hashtable::resize() {
  // Allocate the next size table and swap its memory with table_.
  tableSizesIndex_++;
  std::vector<KeyValue> newTable(tableSizes_[tableSizesIndex_]);
  table_.swap(newTable);

  // Rehash all entries from newTable to table_.
  for (size_t i = 0; i < newTable.size(); i++) {
    if (newTable[i].value > 0) {
      insertNewKeyValue(newTable[i].key, newTable[i].value);
    }
  }
}

int Hashtable::hash(const string& key, int& doubleHashValue) const {
  int a[30] = {}; // Initialize array to all zeros.

  // Copy values of key to the end of array a.
  int n = (int)key.size();
  for (int i = n - 1, j = 29; i >= 0 && j >= 0; i--, j--) {
    a[j] = key[i] - 'a';
  }

  // Compute the value of w[i].
  int k = 0; // Index into array a.
  long long w[5];
  for (int i = 0; i < 5; i++) {
    // From the left to right, keep adding values to w[i] from next value of a.
    long long wi = 0;
    for (int j = 0; j < 6; j++) {
      wi = 26 * wi + a[k];
      k++;
    }
    w[i] = wi;
  }
  long long value =
      r1_ * w[0] + r2_ * w[1] + r3_ * w[2] + r4_ * w[3] + r5_ * w[4];

  if (probing_ == 2) {
    long long p = secondHashPrimes_[tableSizesIndex_];
    doubleHashValue =
        static_cast<int>(p - ((w[0] + w[1] + w[2] + w[3] + w[4]) % p));
  }

  return value % table_.size();
}
