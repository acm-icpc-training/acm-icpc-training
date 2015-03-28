#include <algorithm>
#include <cmath>
#include <cstdio>
#include <unordered_set>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Edge {
  Edge(int input_v1, int input_v2, int input_w) :
    v1(input_v1), v2(input_v2), w(input_w) {}

  int v1;
  int v2;
  int w;
};

class Main {
 public:
  bool Process() {
    if (!ReadInput()) {
      return false;
    }

    int ans = numeric_limits<int>::max();
    for (int i = 0; i < n; i++) {
      ans = min(SolveOneRoot(i), ans);
    }
    cout << ans << endl;
    return true;
  }

 private:
  int n;
  vector<vector<Edge>> adjs;

  bool ReadInput() {
    cin >> n;
    if (n == 0) {
      return false;
    }

    vector<int> ps, ds;
    for (int i = 1; i < n; i++) {
      int p;
      cin >> p;
      ps.push_back(p);
    }
    for (int i = 1; i < n; i++) {
      int d;
      cin >> d;
      ds.push_back(d);
    }

    adjs.assign(n, vector<Edge>());
    for (int i = 0; i < n - 1; i++) {
      int v1 = i + 1;
      int v2 = ps[i] - 1;
      int w = ds[i];
      adjs[v1].push_back(Edge(v1, v2, w));
      adjs[v2].push_back(Edge(v2, v1, w));
    }

    return true;
  }

  int SolveOneRoot(int root) {
    vector<int> dists, costs;
    dists.assign(n, -1);
    costs.assign(n, -1);
    DFS(root, -1, 0, dists, costs);
 
    int max_dist = 0;
    for (int dist : dists) {
      if (dist >= 0) {
        max_dist = max(dist, max_dist);
      }
    }
    return costs[root] - max_dist;
  }

  bool IsLeaf(int v, int parent) {
    for (const auto& edge: adjs[v]) {
      if (edge.v2 == parent) {
        continue;
      }
      return false;
    }
    return true;
  }

  void DFS(int v, int parent, int dist,
           vector<int>& dists, vector<int>& costs) {
    int cost = 0;
    vector<Edge> next_edges;
    for (const auto& edge : adjs[v]) {
      if (edge.v2 == parent) {
        continue;
      }
      if (IsLeaf(edge.v2, v)) {
        cost += edge.w;
        continue;
      }
      next_edges.push_back(edge);
    }
    if (next_edges.size() == 0) {
      dists[v] = dist;
      costs[v] = cost;
      return;
    }
    for (const auto& next_edge : next_edges) {
      DFS(next_edge.v2, v, dist + next_edge.w, dists, costs);
      cost += 3 * next_edge.w + costs[next_edge.v2];
    }
    dists[v] = dist;
    costs[v] = cost;
  }
};

int main() {
  while (Main().Process()) {}
  return 0;
}
