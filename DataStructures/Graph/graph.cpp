#include "graph.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

// List Graph

list_graph::list_graph(int num_nodes) { adj_.resize(num_nodes); }

bool list_graph::add_edge(int v1, int v2, int weight) {
  assert(v1 >= 0 && v1 < size());
  assert(v2 >= 0 && v2 < size());
  if (!edge_exists(v1, v2)) {
    adj_[v1].push_back(edge(v2, weight));
    adj_[v2].push_back(edge(v1, weight));
    return true;
  } else {
    return false;
  }
}

bool list_graph::remove_edge(int v1, int v2) {
  assert(v1 >= 0 && v1 < size());
  assert(v2 >= 0 && v2 < size());
  if (edge_exists(v1, v2)) {
    for (int i = 0; i < adj_[v1].size(); i++) {
      if (adj_[v1][i].neighbor == v2) {
        adj_[v1].erase(adj_[v1].begin() + i);
        break;
      }
    }
    for (int i = 0; i < adj_[v2].size(); i++) {
      if (adj_[v2][i].neighbor == v1) {
        adj_[v2].erase(adj_[v2].begin() + v1);
        break;
      }
    }
    return true;
  } else {
    return false;
  }
}

bool list_graph::edge_exists(int v1, int v2) const {
  assert(v1 >= 0 && v1 < size());
  assert(v2 >= 0 && v2 < size());
  for (int i = 0; i < adj_[v1].size(); i++) {
    if (adj_[v1][i].neighbor == v2) {
      return true;
    }
  }
  return false;
}

std::vector<graph::edge> list_graph::neighbors(int v) const {
  assert(v >= 0 && v < size());
  return adj_[v];
}

// Matrix Graph

matrix_graph::matrix_graph(int num_nodes) {
  matrix_.resize(num_nodes);
  for (int i = 0; i < matrix_.size(); i++) {
    matrix_[i].resize(num_nodes, 0);
  }
}

bool matrix_graph::add_edge(int v1, int v2, int weight) {
  assert(v1 >= 0 && v1 < size());
  assert(v2 >= 0 && v2 < size());
  if (matrix_[v1][v2] == 0) {
    matrix_[v1][v2] = weight;
    matrix_[v2][v1] = weight;
    return true;
  } else {
    return false;
  }
}

bool matrix_graph::remove_edge(int v1, int v2) {
  assert(v1 >= 0 && v1 < size());
  assert(v2 >= 0 && v2 < size());
  if (matrix_[v1][v2] != 0) {
    matrix_[v1][v2] = 0;
    matrix_[v2][v1] = 0;
    return true;
  } else {
    return false;
  }
}

bool matrix_graph::edge_exists(int v1, int v2) const {
  assert(v1 >= 0 && v1 < size());
  assert(v2 >= 0 && v2 < size());
  return matrix_[v1][v2] != 0;
}

std::vector<graph::edge> matrix_graph::neighbors(int v) const {
  std::vector<edge> n;
  for (int i = 0; i < size(); i++) {
    if (matrix_[v][i] != 0) {
      n.push_back(edge(i, matrix_[v][i]));
    }
  }
  return n;
}

void graph::print() const {
  for (int i = 0; i < size(); i++) {
    std::cout << i << " -> ";
    std::vector<graph::edge> n = neighbors(i);
    for (int j = 0; j < n.size(); j++) {
      std::cout << n[j].neighbor << "(" << n[j].weight << ") ";
    }
    std::cout << std::endl;
  }
}

std::vector<int> graph::bfs(int start) const {
  std::vector<int> distances(size(), -1);
  std::vector<bool> visited(size(), false);
  std::queue<int> q;
  q.push(start);
  visited[start] = true;
  distances[start] = 0;
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    std::vector<edge> current_neighbors = neighbors(current);
    for (int i = 0; i < current_neighbors.size(); i++) {
      int n = current_neighbors[i].neighbor;
      if (!visited[n]) {
        visited[n] = true;
        distances[n] = distances[current] + 1;
        q.push(n);
      }
    }
  }
  return distances;
}

std::vector<int> graph::shortest_unweighted_path(int start, int end) {
  assert(start >= 0 && start < size());
  assert(end >= 0 && end < size());
  std::vector<int> path;
  if (start == end) {
    path.push_back(start);
    return path;
  }
  std::vector<int> distances(size(), -1);
  std::vector<bool> visited(size(), false);
  std::vector<int> predecessor(size(), -1);
  std::queue<int> q;
  q.push(start);
  visited[start] = true;
  distances[start] = 0;
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    std::vector<edge> current_neighbors = neighbors(current);
    for (int i = 0; i < current_neighbors.size(); i++) {
      int n = current_neighbors[i].neighbor;
      if (!visited[n]) {
        predecessor[n] = current;
        visited[n] = true;
        distances[n] = distances[current] + 1;
        if (n == end) {
          path.push_back(n);
          while (n != start) {
            n = predecessor[n];
            path.push_back(n);
          }
          std::reverse(path.begin(), path.end());
          return path;
        }
        q.push(n);
      }
    }
  }
  return std::vector<int>();
}

std::vector<int> graph::shortest_distances(int start) {
  std::vector<int> distances(size(), INT_MAX);
  std::vector<bool> visited(size(), false);

  distances[start] = 0;
  while (true) {
    // Find the smallest unvisited node
    int min_dist = INT_MAX;
    int current = -1;
    for (int i = 0; i < size(); i++) {
      if (!visited[i] && distances[i] < min_dist) {
        min_dist = distances[i];
        current = i;
      }
    }
    if (current == -1) {
      break;
    }
    visited[current] = true;
    std::vector<edge> n = neighbors(current);
    for (int i = 0; i < n.size(); i++) {
      int neighbor = n[i].neighbor;
      if (!visited[neighbor]) {
        int d = distances[current] + n[i].weight;
        if (d < distances[neighbor]) {
          distances[neighbor] = d;
        }
      }
    }
  }
  return distances;
}
