#ifndef _S16_GRAPH_H__
#define _S16_GRAPH_H__

#include <vector>

// Abstract Base Class
class graph {
public:
  struct edge {
    edge() {}
    edge(int n, int w) : neighbor(n), weight(w) {}
    int neighbor;
    int weight;
  };
  virtual bool add_edge(int v1, int v2, int weight = 1) = 0;
  virtual int size() const = 0;
  virtual std::vector<edge> neighbors(int v) const = 0;
  virtual bool remove_edge(int v1, int v2) = 0;
  virtual bool edge_exists(int v1, int v2) const = 0;
  virtual ~graph() {}
  // Return distance from root to any node
  // Return -1 if a node is not reachable
  std::vector<int> bfs(int start) const;
  void print() const;

  // Find the shortest path from start to end, ignoring weights
  // The first element of the returned vector is start and the
  // last element is end. Returns empty vector if no valid path
  std::vector<int> shortest_unweighted_path(int start, int end);

  // Djikstra's Algorithm
  std::vector<int> shortest_distances(int start);
};

// Derived
class list_graph : public graph {
public:
  list_graph(int num_nodes);

  int size() const { return adj_.size(); }

  // Returns true if edge is added, false if edge exists
  bool add_edge(int v1, int v2, int weight = 1);

  // Returns true if edge is removed, false if edge does not exist
  bool remove_edge(int v1, int v2);

  // Return true if edge exists, false if it does not
  bool edge_exists(int v1, int v2) const;

  // Gets neighbors of node v
  std::vector<edge> neighbors(int v) const;

private:
  std::vector<std::vector<edge> > adj_;
};

class matrix_graph : public graph {
public:
  matrix_graph(int num_nodes);
  int size() const { return matrix_.size(); }
  bool add_edge(int v1, int v2, int weight = 1);
  bool remove_edge(int v1, int v2);
  bool edge_exists(int v1, int v2) const;
  std::vector<edge> neighbors(int v) const;

private:
  std::vector<std::vector<int> > matrix_;
};

#endif //_S16_GRAPH_H__