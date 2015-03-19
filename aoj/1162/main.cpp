#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAX_NUM_CITY = 30;
const int MAX_SPEED = 30;

struct Edge {
  int from, to, distance, max_speed;
};

struct VertexCost {
  int city, prev, speed;
  double cost;
};

bool GreaterCost(const VertexCost& vc1, const VertexCost& vc2) {
  return vc1.cost > vc2.cost;
}

void Solve(int n, vector<vector<Edge>>& graph, int start, int goal) {
  priority_queue<VertexCost, vector<VertexCost>, decltype(&GreaterCost)>
      pq(&GreaterCost);
  for (const Edge& edge : graph[start]) {
    VertexCost state({edge.to, start, 1, static_cast<double>(edge.distance)});
    pq.push(state);
  }
  vector<vector<vector<bool>>>
      visited(n, vector<vector<bool>>(n, vector<bool>(MAX_SPEED + 1, false)));
  while (!pq.empty()) {
    VertexCost state = pq.top(); pq.pop();
    if (visited[state.city][state.prev][state.speed]) continue;
    visited[state.city][state.prev][state.speed] = true;

    if (state.city == goal && state.speed == 1) {
      cout << state.cost << endl;
      return;
    }

    int curr_city = state.city;
    int curr_prev = state.prev;
    int curr_speed = state.speed;
    for (const auto& edge : graph[state.city]) {
      int next_city = edge.to;
      if (next_city == curr_prev) continue;
      double distance = edge.distance;
      for (int next_speed = curr_speed - 1; next_speed <= curr_speed + 1;
           ++next_speed) {
        if (next_speed <= 0) continue;
        if (next_speed > edge.max_speed) continue;
        double next_cost = state.cost + distance / next_speed;
        VertexCost next({next_city, curr_city, next_speed, next_cost});
        pq.push(next);
      }
    }
  }
  cout << "unreachable" << endl;
}

bool ProcessCase() {
  int n, m;
  cin >> n >> m;
  if (n == 0 && m == 0) return false;
  int start, goal;
  cin >> start >> goal;
  --start;
  --goal;
  vector<vector<Edge>> graph(n, vector<Edge>());
  for (int i = 0; i < m; ++i) {
    int x, y, d, c;
    cin >> x >> y >> d >> c;
    --x;
    --y;
    graph[x].push_back(Edge({x, y, d, c}));
    graph[y].push_back(Edge({y, x, d, c}));
  }
  Solve(n, graph, start, goal);
  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
