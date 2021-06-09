#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#define WS " "
#define LF "\n"
using uint = unsigned int;
using vec = std::vector<int>;
using matrix = std::vector<vec>;
using p = std::pair<int, int>;
using pp = std::pair<int, p>;
using pv = std::vector<pp>;

// Kruskal
void setK(int n, vec &parent, vec &rank) {
  for (int i = 0; i <= n; ++i) {
    parent[i] = i;
    rank[i] = 0;
  }
}

int findK(int i, vec &parent) {

  if (parent[i] != i) {
    parent[i] = findK(parent[i], parent);
  }

  return parent[i];
}

void linkK(int u, int v, vec &parent, vec &rank) {
  if (rank[u] > rank[v]) {
    parent[v] = u;
  } else {
    parent[u] = v;
  }

  if (rank[u] == rank[v]) {
    rank[v]++;
  }
}

void unionK(int u, int v, vec &parent, vec &rank) {
  linkK(findK(u, parent), findK(v, parent), parent, rank);
}

bool PCompare(pp a, pp b) { return a.first < b.first; }

int kruskal(const matrix &graph, const vec &circuit, int n) {
  vec parent(n + 1);
  vec rank(n + 1);
  pv weights;

  // Loop through components and add significant graph connection values to a
  // list
  setK(n, parent, rank);
  int csize = (int)circuit.size();
  for (int c = 0; c < csize; ++c) {
    for (int k = 0; k < csize; ++k) {
      if (c == k) {
        continue;
      }

      if (graph[circuit[c]][circuit[k]] != 0) {
        weights.push_back(
            std::make_pair(graph[circuit[c]][circuit[k]],
                           std::make_pair(circuit[c], circuit[k])));
      }
    }
  }

  int longest = 0;

  // sort the graph list
  std::sort(weights.begin(), weights.end(), PCompare);

  // Loop thorugh the weights and check if there is any union between 2 sorted
  // vertexes
  for (auto w : weights) {
    int u = w.second.first;
    int v = w.second.second;

    if (findK(u, parent) != findK(v, parent)) {
      unionK(u, v, parent, rank);
      longest += w.first;
    }
  }

  // Return the sum of the distances between connected points
  return longest;
}

// Tarjan
void tarjan(const int v, const matrix &graph, vec &dfs, vec &low, matrix &scc,
            vec &stacked, uint &index) {
  static std::stack<int> s;
  dfs[v] = low[v] = index++;
  s.push(v);
  stacked[v] = true;
  for (int i = 0; i < (int)graph[v].size(); i++) {
    if (graph[v][i] != 0) {
      if (dfs[i] == -1) {
        tarjan(i, graph, dfs, low, scc, stacked, index);
        low[v] = std::min(low[v], low[i]);
      } else if (stacked[i] == true) {
        low[v] = std::min(low[v], dfs[i]);
      }
    }
  }
  if (dfs[v] == low[v]) {
    vec temp;
    int u;
    do {
      u = s.top();
      s.pop();
      stacked[u] = false;
      temp.push_back(u);
    } while (v != u);
    scc.push_back(temp);
  }
}

int main() {
  // Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  // End of Fast(er) I/O

  int testCases;
  int POIs, conns, questions;
  uint startPoint, endPoint, distance, index;
  int circuits, largest, longest, total;
  int comp;
  std::cin >> testCases;

  for (int i = 0; i < testCases; ++i) {
    std::cin >> POIs >> conns >> questions;

    matrix graph(POIs, vec(POIs, 0));
    matrix scc;
    vec dfs(POIs, -1);
    vec low(POIs);
    if (conns == 0) {
      for (int c = 0; c < questions; ++c) {
        if (c < questions - 1) {
          std::cout << "0" << WS;
        } else {
          std::cout << "0";
        }
      }
      std::cout << LF;
      continue;
    }

    for (int j = 0; j < conns; ++j) {
      std::cin >> startPoint >> endPoint >> distance;
      startPoint--;
      endPoint--;
      graph[startPoint][endPoint] = distance;
    }

    vec stacked(POIs, 0);
    index = 0;

    for (int i = 0; i < POIs; ++i) {
      if (dfs[i] == -1) {
        tarjan(i, graph, dfs, low, scc, stacked, index);
      }
    }

    total = 0;
    circuits = 0;
    largest = 0;
    longest = 0;

    for (auto i : scc) {
      int k = i.size();

      if (k == 1) {
        continue;
      }

      circuits++;
      largest = std::max(largest, k);
      if (questions >= 3) {
        comp = kruskal(graph, i, POIs);
        total += comp;
        longest = std::max(longest, comp);
      }
    }

    if (circuits == 0) {
      largest = 0;
      longest = 0;
      total = 0;
    }

    std::cout << circuits;

    if (questions >= 2) {
      std::cout << WS << largest;
    }

    if (questions >= 3) {
      std::cout << WS << longest;
    }

    if (questions == 4) {
      std::cout << WS << total;
    }

    std::cout << LF;
  }

  return 0;
}