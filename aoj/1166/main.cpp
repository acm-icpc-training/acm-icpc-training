#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct State {
  int x, y, distance;
};

bool ProcessCase() {
  int w, h;
  cin >> w >> h;
  if (w == 0 && h == 0) {
    return false;
  }

  vector<vector<int>> ver_wall;
  ver_wall.assign(h, vector<int>(w - 1, 0));
  vector<vector<int>> hor_wall;
  hor_wall.assign(h - 1, vector<int>(w, 0));
  for (int y = 0; y < h - 1; ++y) {
    for (int x = 0; x < w - 1; ++x) {
      cin >> ver_wall[y][x];
    }
    for (int x = 0; x < w; ++x) {
      cin >> hor_wall[y][x];
    }
  }
  for (int x = 0; x < w - 1; ++x) {
    cin >> ver_wall[h - 1][x];
  }

  vector<vector<int>> distance;
  distance.assign(h, vector<int>(w, -1));
  queue<State> queue;
  queue.push(State({0, 0, 1}));
  while (!queue.empty()) {
    const auto s = queue.front();
    queue.pop();

    if (distance[s.y][s.x] >= 0) {
      continue;
    }
    distance[s.y][s.x] = s.distance;

    // Right
    if (s.x + 1 < w && !ver_wall[s.y][s.x]) {
      queue.push(State({s.x + 1, s.y, s.distance + 1}));
    }
    // Down
    if (s.y + 1 < h && !hor_wall[s.y][s.x]) {
      queue.push(State({s.x, s.y + 1, s.distance + 1}));
    }
    // Left
    if (s.x - 1 >= 0 && !ver_wall[s.y][s.x - 1]) {
      queue.push(State({s.x - 1, s.y, s.distance + 1}));
    }
    // Up
    if (s.y - 1 >= 0 && !hor_wall[s.y - 1][s.x]) {
      queue.push(State({s.x, s.y - 1, s.distance + 1}));
    }
  }
  if (distance[h - 1][w - 1] < 0) {
    cout << 0 << endl;
  } else {
    cout << distance[h - 1][w - 1] << endl;
  }
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}
