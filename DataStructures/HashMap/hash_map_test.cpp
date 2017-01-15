#include "../test/logging.h"
#include "hash_map.h"
#include "key_value.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void StringIntHash() {
  hash_map<int> h(19);
  CHECK_EQ(h["dog"], 0);
  int &d = h["dog"];
  d = 10;
  CHECK_EQ(h["dog"], 10);
  d = 20;
  CHECK_EQ(h["dog"], 20);
  CHECK_NE(h["dog"], 0);
}

struct Player {
  Player() {}
  Player(string t, int n) : team(t), number(n) {}
  string team;
  int number;
};

ostream &operator<<(ostream &os, Player p) {
  os << " Team: " << p.team << " Number: " << p.number << endl;
  return os;
}

void StringPlayerHash() {
  hash_map<Player> h(20);
  Player jordan("Bulls", 23);
  Player curry("Warriors", 30);
  h["Jordan"] = jordan;
  h["Curry"] = curry;

  string name1 = "Jordan";
  string name2 = "Curry";

  cout << "Name: " << name1 << h["Jordan"];
  cout << "Name: " << name2 << h["Curry"];

  Player *p = h.find("Jordan");
  CHECK_EQ(p == nullptr, false);
  p->number = 24;
  CHECK_EQ(h["Jordan"].number, 24);
  CHECK_EQ(h.find("Filip") == nullptr, true);
}

int main() {
  BEGIN_TESTS();
  StringIntHash();
  StringPlayerHash();

  return 0;
}