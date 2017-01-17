#include "network.h"
#include "user.h"
#include <iomanip>
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Provide a filename" << endl;
    return 1;
  }
  Network network;
  network.read_friends(argv[1]);
  network.print_users();
  while (true) {
    cout << "Option 1, Add User: Name, Birth Year, Zip Code" << endl;
    cout << "Option 2, Add Friend Connection: Provide 2 Usernames" << endl;
    cout << "Option 3, Remove Friend Connection: Provide 2 Usernames" << endl;
    cout << "Option 4, Print Users" << endl;
    cout << "Option 5, List Friends: Provide Username" << endl;
    cout << "Option 6, Write to File" << endl;

    cout << "Option 7, Compute Shortest Distance: Enter 2 Users" << endl;
    cout << "Option 8, Print disjoint sets" << endl;
    cout << "Option 9, Friend Suggestions: Enter User" << endl;
    cout << "Other inputs will exit program" << endl;
    int input;
    cin >> input;
    if (input == 1) {
      string first_name, last_name;
      int year;
      int zipcode;
      cin >> first_name >> last_name >> year >> zipcode;
      string name = first_name + " " + last_name;
      network.add_user(name, year, zipcode);
    } else if (input == 2) {
      string first_name1, last_name1, first_name2, last_name2;
      cin >> first_name1 >> last_name1 >> first_name2 >> last_name2;
      string user1 = first_name1 + " " + last_name1;
      string user2 = first_name2 + " " + last_name2;
      int value = network.add_connection(user1, user2);
      if (value != 0) {
        cout << "Could not add connection between "
             << user1 << " and " << user2 << endl;
      }
    } else if (input == 3) {
      string first_name1, last_name1, first_name2, last_name2;
      cin >> first_name1 >> last_name1 >> first_name2 >> last_name2;
      string user1 = first_name1 + " " + last_name1;
      string user2 = first_name2 + " " + last_name2;
      int value = network.remove_connection(user1, user2);
      if (value != 0) {
        cout << "Could not remove connection between "
             << user1 << " and " << user2 << endl;
      }
    } else if (input == 4) {
      network.print_users();
    } else if (input == 5) {
      string first_name, last_name;
      cin >> first_name >> last_name;
      string name = first_name + " " + last_name;
      bool name_found = false;
      for (int i = 0; i < network.size(); i++) {
        if (network.user(i).get_name() == name) {
          name_found = true;
          vector<int> friends = network.user(i).friends();
          cout << "ID" << setw(7) << "Name" << setw(17) << "Year" << setw(6)
             << "Zip" << endl;
          cout << "========================================" << endl;
          for (int j = 0; j < friends.size(); j++) {
            int friend_id = friends[j];
            cout << j << "." << setw(16) << network.user(friend_id).get_name() << setw(8)
            << network.user(friend_id).get_dob() << setw(8) << network.user(friend_id).get_zip() << endl;
          }
        }
      }
      if (!name_found) {
        cout << "User not found" << endl;
      }
    } else if (input == 6) {
      string filename;
      cin >> filename;
      network.write_friends(filename.c_str());
    } else if (input == 7) {
      string first_name1, last_name1, first_name2, last_name2;
      cin >> first_name1 >> last_name1 >> first_name2 >> last_name2;
      string user1 = first_name1 + " " + last_name1;
      string user2 = first_name2 + " " + last_name2;
      int from = network.get_id(user1);
      int to = network.get_id(user2);
      if (from == -1 || to == -1) {
        cout << "Not valid users" << endl;
      } else {
        vector<int> sp = network.shortest_path(from, to);
        if (sp.empty()) {
          cout << "Could not reach " << network.user(to).get_name() << endl;
        } else {
          cout << "Distance: " << sp.size() << endl;
          cout << network.user(sp[0]).get_name();
          for (int i = 1; i < sp.size(); i++) {
            cout << " -> " << network.user(sp[i]).get_name();
          }
          cout << endl;
        }
      }
    } else if (input == 8) {
      vector<vector<int> > groups = network.groups();
      for (int i = 0; i < groups.size(); i++) {
        cout << "Set " << i + 1 << " => ";
        vector<int> group = groups[i];
        for (int j = 0; j < group.size(); j++) {
          cout << network.user(group[j]).get_name();
          if (j < group.size()-1) {
            cout << ", ";
          }
        }
        cout << endl;
      }
    } else if (input == 9) {
      string first_name, last_name;
      cin >> first_name >> last_name;
      string user = first_name + " " + last_name;
      int who = network.get_id(user);
      // Compute friend suggestions, relational distance max: 2
      // The suggested friend(s) is/are:
      // Chip Kelly Score: 3
      // John Harbaugh Score: 3
      // Print None if no candidates
      int score;
      vector<int> suggested_friends = network.suggest_friends(who, score);
      cout << "The suggested friend(s) is/are:" << endl;
      if (suggested_friends.empty()) {
        cout << "None" << endl;
      } else {
        for (int i = 0; i < suggested_friends.size(); i++) {
          cout << network.user(suggested_friends[i]).get_name() << setw(10) << "Score: " << score << endl;
        }
      }
    } else {
      break;
    }
    cout << endl;
  }
  return 0;
}
