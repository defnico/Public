#include "../test/logging.h"
#include "key_value.h"
#include "list_map.h"
#include <algorithm>
#include <cstddef>
#include <string>

#include <iostream>
using namespace std;

struct Player {
  Player(string nm, string t, int n) : name(nm), team(t), number(n) {}
  string name;
  string team;
  int number;
};

typedef list_map<string, Player> PlayerMap;
typedef key_value<string, Player> KV;
typedef list_map<string, Player>::iter PlayerMapIter;

ostream &operator<<(ostream &os, Player p) {
  os << p.name << ": " << p.team << ", " << p.number << endl;
  return os;
}

void AddPlayer(PlayerMap *player_map, string name, string team, int number) {
  Player player(name, team, number);
  player_map->insert(KV(name, player));
}

int main() {
  BEGIN_TESTS();

  PlayerMap m;
  CHECK_EQ(m.empty(), true);

  AddPlayer(&m, "Kobe Bryant", "Lakers", 24);
  AddPlayer(&m, "Stephen Curry", "Warriors", 30);
  AddPlayer(&m, "Michael Jordan", "Bulls", 23);
  AddPlayer(&m, "Shaquille O'Neal", "Magic", 34);
  AddPlayer(&m, "LeBron James", "Cavaliers", 23);
  AddPlayer(&m, "Klay Thompson", "Warriors", 11);
  AddPlayer(&m, "Kyrie Irving", "Cavliers", 2);
  AddPlayer(&m, "Tristian Thompson", "Cavliers", 13);

  cout << m << endl;

  // Search database
  while (true) {
    string name;
    cout << "Enter player name, or Q to quit: ";
    cin >> name;
    if (name == "q" || name == "Q") {
      break;
    }
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    PlayerMapIter it = m.begin();
    while (it != m.end()) {
      string key = it.data().key;
      transform(key.begin(), key.end(), key.begin(), ::tolower);

      string::size_type index = key.find(name);
      if (index != string::npos) {
        cout << it.data().value << endl;
      }
      it = it.next();
    }
  }
}