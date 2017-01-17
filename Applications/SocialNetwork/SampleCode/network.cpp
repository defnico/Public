#include "network.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

int Network::read_friends(const char* filename) {
  ifstream ifs(filename);
  int num_users;
  ifs >> num_users;
  if (ifs.fail()) {
    cout << "Read failed" << endl;
    return -1;
  }
  users_.resize(num_users);
  for (int i = 0; i < num_users; i++) {
    int id, zip, year;
    string first_name, last_name;
    ifs >> id >> first_name >> last_name >> year >> zip;
    string name = first_name + " " + last_name;
    User user(id, name, year, zip);
    users_[id] = user;
    string str;
    getline(ifs, str);
    getline(ifs, str);
    stringstream ss(str);
    int id2;
    cout << "id = " << id << endl;
    while (ss >> id2) {
      cout << "adding friend between = " << id <<
      " and " << id2 << endl;
      users_[id].add_friend(id2);
    }
  }
  return 0;
}

int Network::write_friends(const char* filename) {
  ofstream ofs(filename);
  ofs << users_.size() << endl;
  for (int i = 0; i < users_.size(); i++) {
    ofs << i << endl;
    ofs << '\t' << users_[i].get_name() << endl;
    ofs << '\t' << users_[i].get_dob() << endl; 
    ofs << '\t' << users_[i].get_zip() << endl;
    vector<int> friends = users_[i].friends();
    ofs << '\t';
    for (int j = 0; j < friends.size(); j++) {
      ofs << friends[j] << " ";
    }
    ofs << endl;
  }
  return 0;
}

void Network::add_user(string username, int yr, int zipcode) {
  int id = users_.size();
  User new_user(id, username, yr, zipcode);
  users_.push_back(new_user);
}

int Network::add_connection(string name1, string name2) {
  int id1 = get_id(name1);
  int id2 = get_id(name2);
  if (id1 == -1 || id2 == -1) {
    cout << "Connection not added between " << name1 << " and " << name2 << endl;
    return -1;
  } else {
    cout << "Adding connection between " << name1 << " and " << name2 << endl;
    users_[id1].add_friend(id2);
    users_[id2].add_friend(id1);
    return 0;
  }
}

int Network::remove_connection(string name1, string name2) {
  int id1 = get_id(name1);
  int id2 = get_id(name2);
  if (id1 == -1 || id2 == -1) {
    cout << "Connection was not deleted" << endl;
    return -1;
  } else {
    cout << "Deleting connection between " << name1 << " and " << name2 << endl;
    users_[id1].delete_friend(id2);
    users_[id2].delete_friend(id1);
    return 0;
  }
}

int Network::get_id(string username) {
  for (int i = 0; i < users_.size(); i++) {
    if (username == users_[i].get_name()) {
      return users_[i].get_id();
    }
  }
  return -1;
}

void Network::print_users() {
  cout << "ID" << setw(7) << "Name" << setw(17) << "Year" << setw(6)
             << "Zip" << endl;
        cout << "========================================" << endl;
  for (int i = 0; i < users_.size(); i++) {
    cout << i << "." << setw(16) << users_[i].get_name() << setw(8)
    << users_[i].get_dob() << setw(8) << users_[i].get_zip() << endl;
  }
}

void Network::bfs(int start) {
  queue<int> q;
  for (int i = 0; i < size(); i++) {
    users_[i].predecessor = -1;
    users_[i].depth = -1;
  }
  q.push(start);
  users_[start].depth = 0;
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    vector<int> friends = users_[current].friends();
    for (int j = 0; j < friends.size(); j++) {
      int friend_id = friends[j];
      if (users_[friend_id].depth == -1) {
        users_[friend_id].depth = users_[current].depth + 1;
        users_[friend_id].predecessor = current;
        q.push(friend_id);
      }
    }
  }
}

vector<int> Network::shortest_path(int from, int to) {
  // Call bfs to set distance and predecessor for each user
  bfs(from);

  // Use predecessors to make path between from and to
  vector<int> path;
  if (users_[to].depth == -1) {
    return path;
  }
  int id = to;
  while (id != from) {
    path.push_back(id);
    id = users_[id].predecessor;
  }
  path.push_back(from);

  // Reverse the path
  reverse(path.begin(), path.end());
  return path;
}

vector<vector<int> > Network::groups() {
  vector<vector<int> > output;
  vector<bool> group_found(size(), false);
  for (int i = 0; i < size(); i++) {
    if (!group_found[i]) {
      bfs(i);
      vector<int> group;
      for (int j = 0; j < size(); j++) {
        if (users_[j].depth >= 0) {
          group.push_back(j);
          group_found[j] = true;
        }
      }
      output.push_back(group);
    }
  }
  return output;
}

int Network::num_common_friends(int user1, int user2) {
  vector<int> friends1 = users_[user1].friends();
  vector<int> friends2 = users_[user2].friends();
  int num_common = 0;
  for (int i = 0; i < friends1.size(); i++) {
    for (int j = 0; j < friends2.size(); j++) {
      if (friends2[j] == friends1[i]) {
        num_common++;
      }
    }
  }
  return num_common;
}

vector<int> Network::suggest_friends(int who, int& score) {
  vector<int> scores(size(), -1);
  bfs(who);
  score = -1;
  for (int i = 0; i < size(); i++) {
    if (users_[i].depth == 2) {
      scores[i] = num_common_friends(who, i);
      score = max(score, scores[i]);
    }
  }
  vector<int> suggested_friends;
  for (int i = 0; i < size(); i++) {
    if (scores[i] == score) {
      suggested_friends.push_back(i);
    }
  }
  return suggested_friends;
}
