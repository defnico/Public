#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"
#include <string>

class Network {
public:
  Network() { }
  ~Network() { }
  int read_friends(const char* filename);
  int write_friends(const char* filename);
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  void print_users();
  int size() { return users_.size(); }
  User user(int i) { return users_[i]; }

  vector<int> shortest_path(int from, int to);
  vector<vector<int> > groups();
  vector<int> suggest_friends(int who, int& score);
  int num_common_friends(int user1, int user2);
  void bfs(int start);

private:
  vector<User> users_;
};

#endif
