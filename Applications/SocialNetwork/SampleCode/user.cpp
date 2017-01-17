#include "user.h"
#include <iostream>
using namespace std;

User::User(int id, string name, int year, int zip) {
  id_ = id;
  name_ = name;
  year_ = year;
  zip_ = zip;
}

void User::add_friend(int id) {
  for (int i = 0; i < friends_.size(); i++) {
    if (id == friends_[i]) {
      return;
    }
  }
  friends_.push_back(id);
}

void User::delete_friend(int id) {
  int num_friends = friends_.size();
  for (int i = 0; i < num_friends; i++) {
    if (id == friends_[i]) {
      for (int j = i; j < num_friends-1; j++) {
        friends_[j] = friends_[j + 1];
      }
      friends_.resize(num_friends - 1);
      cout << "Friend " << name_ << " with ID " << id << " deleted" << endl;
      return;
    }
  }
  cout << "NO friend of " << name_ << " with ID " << id << " deleted" << endl;
}
