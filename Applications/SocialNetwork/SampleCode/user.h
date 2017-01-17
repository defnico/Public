#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
using namespace std;

class User {
public:
  User(int id, string name, int year, int zip);
  User() { }
  ~User() { }
  void add_friend(int id);
  void delete_friend(int id);
  int get_id() { return id_; }
  string get_name() { return name_; }
  int get_dob() { return year_; }
  int get_zip() { return zip_; }
  vector<int> friends() { return friends_; }

  int depth;
  int predecessor;

private:
  int id_;
  string name_;
  int year_;
  int zip_;
  vector<int> friends_;
};

#endif
