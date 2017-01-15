#include "../test/logging.h"
#include "graph.h"
#include <iostream>
#include <vector>

void print_path(std::vector<int> path) {
  std::cout << path[0];
  for (int i = 1; i < path.size(); i++) {
    std::cout << " -> " << path[i];
  }
  std::cout << std::endl;
}

void list_graph_test() {
  list_graph g(8);
  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(2, 5);
  g.add_edge(3, 4);
  g.add_edge(3, 6);
  g.add_edge(4, 6);
  g.add_edge(5, 7);

  std::vector<graph::edge> n = g.neighbors(0);
  CHECK_EQ(n.size(), 2);

  g.print();
}

void bfs_test() {
  // List graph
  list_graph g(12);
  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(2, 5);
  g.add_edge(3, 6);
  g.add_edge(6, 8);
  g.add_edge(5, 7);
  g.add_edge(7, 9);
  g.add_edge(8, 9);
  g.add_edge(9, 10);
  g.print();
  std::vector<int> distances = g.bfs(5);
  for (int i = 0; i < g.size(); i++) {
    std::cout << "distances[" << i << "] = " << distances[i] << std::endl;
  }
}

void matrix_graph_test() {
  matrix_graph m(8);
  m.add_edge(0, 1);
  m.add_edge(0, 2);
  m.add_edge(1, 2);
  m.add_edge(2, 3);
  m.add_edge(2, 5);
  m.add_edge(3, 4);
  m.add_edge(3, 6);
  m.add_edge(4, 6);
  m.add_edge(5, 7);

  std::vector<graph::edge> n = m.neighbors(0);

  m.print();
}

void matrix_bfs_test() {
  // Matrix graph
  matrix_graph g(12);
  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(2, 5);
  g.add_edge(3, 6);
  g.add_edge(6, 8);
  g.add_edge(5, 7);
  g.add_edge(7, 9);
  g.add_edge(8, 9);
  g.add_edge(9, 10);
  g.print();
  std::vector<int> distances = g.bfs(5);
  for (int i = 0; i < g.size(); i++) {
    std::cout << "distances[" << i << "] = " << distances[i] << std::endl;
  }
  print_path(g.shortest_unweighted_path(0, 9));
  print_path(g.shortest_unweighted_path(2, 10));
}

void neighbors_test() {
  matrix_graph n(9);
  n.add_edge(0, 1, 4);
  n.add_edge(0, 7, 8);
  n.add_edge(1, 2, 8);
  n.add_edge(1, 7, 11);
  n.add_edge(7, 8, 7);
  n.add_edge(7, 6, 1);
  n.add_edge(6, 8, 6);
  n.add_edge(6, 5, 2);
  n.add_edge(2, 8, 2);
  n.add_edge(2, 5, 4);
  n.add_edge(2, 3, 7);
  n.add_edge(3, 5, 14);
  n.add_edge(3, 4, 9);
  n.add_edge(4, 5, 10);
  n.print();
}

void djikstras_test() {
  matrix_graph n(9);
  n.add_edge(0, 1, 4);
  n.add_edge(0, 7, 8);
  n.add_edge(1, 2, 8);
  n.add_edge(1, 7, 11);
  n.add_edge(7, 8, 7);
  n.add_edge(7, 6, 1);
  n.add_edge(6, 8, 6);
  n.add_edge(6, 5, 2);
  n.add_edge(2, 8, 2);
  n.add_edge(2, 5, 4);
  n.add_edge(2, 3, 7);
  n.add_edge(3, 5, 14);
  n.add_edge(3, 4, 9);
  n.add_edge(4, 5, 10);
  std::vector<int> distances = n.shortest_distances(0);
  for (int i = 0; i < distances.size(); i++) {
    std::cout << i << ": " << distances[i] << std::endl;
  }
}

int main() {
  // list_graph_test();
  // bfs_test();
  // matrix_graph_test();
  // matrix_bfs_test();
  // neighbors_test();
  djikstras_test();
  return 0;
}