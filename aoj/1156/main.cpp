#include <cstdlib>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

const int DXS[] = {1, 0, -1, 0};
const int DYS[] = {0, 1, 0, -1};

struct VertexCost {
  int x, y, dir;
  int cost;
  string VertexID() {
    stringstream ss;
    ss << "(" << x << "," << y << "," << dir << ")";
    return ss.str();
  }
};

bool GreaterCost(VertexCost& vc1, VertexCost& vc2) {
  return vc1.cost > vc2.cost;
}

class Main {
  int w, h;
  vector<vector<int>> map;
  vector<int> costs;

 public:
  bool ProcessCase() {
    cin >> w >> h;
    if (w == 0 && h == 0) return false;

    map.assign(h, vector<int>(w, 0));
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        cin >> map[y][x];
      }
    }

    costs.assign(4, 0);
    for (int i = 0; i < 4; ++i) {
      cin >> costs[i];
    }

    priority_queue<VertexCost, vector<VertexCost>, decltype(&GreaterCost)>
        pq(&GreaterCost);
    unordered_set<string> visited;

    VertexCost start({0, 0, 0, 0});
    pq.push(start);
    while (!pq.empty()) {
      VertexCost vertex_cost = pq.top();
      pq.pop();
      string vertex_id = vertex_cost.VertexID();
      if (visited.find(vertex_id) != visited.end()) continue;
      visited.insert(vertex_id);

      int x = vertex_cost.x;
      int y = vertex_cost.y;
      int dir = vertex_cost.dir;
      int cost = vertex_cost.cost;

      if (x == w - 1 && y == h - 1) {
        cout << cost << endl;
        return true;
      }

      for (int command = 0; command < 4; ++command) {
        int next_dir = (dir + command) % 4;
        int next_x = x + DXS[next_dir];
        int next_y = y + DYS[next_dir];
        int next_cost = cost + ((command == map[y][x]) ? 0 : costs[command]);
        if (next_x < 0 || w <= next_x || next_y < 0 || h <= next_y) continue;
        VertexCost next({next_x, next_y, next_dir, next_cost});
        pq.push(next);
      }
    }
    cerr << "Did not reach the goal!" << endl;
    exit(1);
  }
};

int main() {
  while (Main().ProcessCase());
  return 0;
}
