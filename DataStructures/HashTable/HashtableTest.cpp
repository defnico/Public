#include "Hashtable.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace std;

// Test the hash function.
TEST(HashtableTest, HashFunction) {
  // Create a derived class to get access to the protected hash function.
  struct HashTest : public Hashtable {
    HashTest() : Hashtable(true, 0) {}
    int doubleHashValue;
    int Hash(string key) { return hash(key, doubleHashValue); }
    int size() const { return table_.size(); }
  };

  HashTest hashTest;
  EXPECT_EQ(11, hashTest.size());

  int cHashKey = hashTest.Hash("c");
  EXPECT_EQ((2 * 261934300LL) % hashTest.size(), cHashKey);

  int cdHashKey = hashTest.Hash("cd");
  EXPECT_EQ(((26 * 2 + 3) * 261934300LL) % hashTest.size(), cdHashKey);

  int cdeHashKey = hashTest.Hash("cde");
  EXPECT_EQ(((26 * 26 * 2 + 26 * 3 + 4) * 261934300LL) % hashTest.size(),
            cdeHashKey);
  int catHashKey = hashTest.Hash("cat");
  EXPECT_EQ(((26 * 26 * 2 + 26 * 0 + 19) * 261934300LL) % hashTest.size(),
            catHashKey);
}

TEST(HashtableTest, Add) {
  Hashtable hashTable(true, 0); // Linear probing.
  EXPECT_EQ(0, hashTable.count("c"));

  hashTable.add("c");
  EXPECT_EQ(1, hashTable.count("c"));

  hashTable.add("c");
  EXPECT_EQ(2, hashTable.count("c"));
}

TEST(HashtableTest, AddLongestAllowable) {
  Hashtable hashTable(true, 1); // Quadratic probing.

  // Try the longest allowable word.
  const string word28 = "Antidisestablishmentarianism";
  hashTable.add(word28);
  EXPECT_EQ(1, hashTable.count(word28));

  hashTable.add(word28);
  EXPECT_EQ(2, hashTable.count(word28));

  const string word27 = "Honorificabilitudinitatibus";
  hashTable.add(word27);
  EXPECT_EQ(1, hashTable.count(word27));

  hashTable.add(word27);
  EXPECT_EQ(2, hashTable.count(word27));
}

TEST(HashtableTest, DoubleHashing) {
  Hashtable hashTable(true, 2);   // Double hashing.
  for (int i = 1; i <= 28; i++) { // Up to longest allowable word.
    for (char c = 'a'; c <= 'z'; c++) {
      string cStr(i, c); // Create a word of with a single repeated character.
      hashTable.add(cStr);
      EXPECT_EQ(1, hashTable.count(cStr));
    }
  }
}
