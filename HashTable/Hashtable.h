#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>

struct KeyValue {
  KeyValue(std::string k, int v) : key(k), value(v) {}
  KeyValue() : value(0) {}
  std::string key;
  int value;
};

class Hashtable {
public:
  Hashtable(bool debug, unsigned int probing);
  ~Hashtable();

  // Add a key to the table.  Insert and set count to 1 if it is a new key and
  // and otherwise increment the count for that key.
  // Resizes if load factor is equal or greater than 0.5.
  void add(std::string key);

  // Return the number of times key was added. Return 0 if never added.
  int count(std::string key) const;

  // Print the count for all the key, value pairs and output the results.
  void reportAll(std::ostream& os) const;

  // Return the table size for debugging.
  int tableSize() const { return table_.size(); }

  // Return the number entries with non-zero values in the table.
  int numUniqueEntries() const { return numEntries_; }

protected:
  // Return the fraction of non-zero table entries.
  double loadFactor() const { return (double)numEntries_ / table_.size(); }

  // Resize the table to the next table size as given by tableSizes_.
  void resize();

  // Has the given key. Set doubleHashValue if probing == 2.
  int hash(const std::string& key, int& doubleHashValue) const;

  // Get the hashKey for the given starting hashkey and the number of times
  // the hash was attempted.
  int probe(int startHashKey, int count, int doubleHashValue) const;

  // Insert a new <key,value> pair into the current table.
  void insertNewKeyValue(std::string key, int value);

  // The vector of <key,value> pairs for the hash table.
  // key will be 0 if the table entry is not used.
  std::vector<KeyValue> table_;

  // Debug flag for random number generation.  True, use a fixed set for the ri.
  // Otherwise generate them using std::rand.
  bool debug_;

  // Probing algorithm to use. 0: linear, 1: quadratic, 2: double hashing.
  int probing_;

  // Number of non-zero entries in the table.
  int numEntries_;

  // Hash function constants for debug mode.
  int r1_ = 983132572;
  int r2_ = 1468777056;
  int r3_ = 552714139;
  int r4_ = 984953261;
  int r5_ = 261934300;

  int tableSizesIndex_;

  long long w_[5];

  const std::vector<int> tableSizes_ = {
      11,        23,        47,        97,        197,      397,
      797,       1597,      3203,      6421,      12853,    25717,
      51437,     102877,    205759,    411527,    823117,   1646237,
      3292489,   6584983,   13169977,  26339969,  52679969, 105359969,
      210719881, 421439783, 842879579, 1685759167};

  const std::vector<int> secondHashPrimes_ = {
      7,         19,        43,        89,        193,      389,
      787,       1583,      3191,      6397,      12841,    25703,
      51431,     102871,    205721,    411503,    823051,   1646221,
      3292463,   6584957,   13169963,  26339921,  52679927, 105359939,
      210719881, 421439749, 842879563, 1685759113};
};

#endif
