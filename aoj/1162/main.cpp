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
  int VertexID() {
    int id = city;
    id = MAX_NUM_CITY * id + prev;
    id = (MAX_SPEED + 1) * id + speed;
    return id;
  }
};

bool GreaterCost(const VertexCost& vc1, const VertexCost& vc2) {
  return vc1.cost > vc2.cost;
}

void Solve(int n, vector<vector<Edge>>& graph, int start, int goal) {
  priority_queue<VertexCost, vector<VertexCost>, decltype(&GreaterCost)>
      pq(&GreaterCost);
  unordered_map<int, double> vertex_id_to_min;
  for (const Edge& edge : graph[start]) {
    VertexCost state({edge.to, start, 1, static_cast<double>(edge.distance)});
    pq.push(state);
    int vertex_id = state.VertexID();
    if (vertex_id_to_min.find(vertex_id) == vertex_id_to_min.end()) {
      vertex_id_to_min[vertex_id] = state.cost;
    } else if (state.cost < vertex_id_to_min[vertex_id]) {
      vertex_id_to_min[vertex_id] = state.cost;
    } else {
      continue;
    }
  }
  unordered_set<int> visited;
  while (!pq.empty()) {
    VertexCost state = pq.top();
    pq.pop();
    int vertex_id = state.VertexID();
    if (visited.find(vertex_id) != visited.end()) continue;
    visited.insert(vertex_id);

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
        int next_vertex_id = next.VertexID();
        if (vertex_id_to_min.find(next_vertex_id) == vertex_id_to_min.end()) {
          vertex_id_to_min[next_vertex_id] = next.cost;
        } else if (next.cost < vertex_id_to_min[next_vertex_id]) {
          vertex_id_to_min[next_vertex_id] = next.cost;
        } else {
          continue;
        }
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
