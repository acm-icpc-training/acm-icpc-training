#include <iostream>
#include <vector>

using namespace std;

void DFS(const vector<vector<int>>& map, int w, int h,
         int x, int y, vector<vector<bool>>* visited) {
  if ((*visited)[y][x]) return;
  (*visited)[y][x] = true;
  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      if (dy == 0 && dx == 0) continue;
      int nx = x + dx;
      int ny = y + dy;
      if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
      if (map[ny][nx] == 0) continue;
      DFS(map, w, h, nx, ny, visited);
    }
  }
}

bool ProcessCase() {
  int w, h;
  cin >> w >> h;
  if (w == 0 && h == 0) {
    return false;
  }

  vector<vector<int>> map;
  map.assign(h, vector<int>(w, 0));
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      cin >> map[y][x];
    }
  }
  vector<vector<bool>> visited;
  visited.assign(h, vector<bool>(w, 0));

  int count = 0;
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (map[y][x] == 1 && !visited[y][x]) {
        ++count;
        DFS(map, w, h, x, y, &visited);
      }
    }
  }

  cout << count << endl;
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}