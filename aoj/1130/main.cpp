#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int DXS[] = {1, 0, -1, 0};
const int DYS[] = {0, 1, 0, -1};

void DFS(const vector<vector<char>>& map, int w, int h,
         int x, int y, vector<vector<int>>& visited) {
  if (visited[y][x]) return;
  visited[y][x] = true;
  for (int d = 0; d < 4; ++d) {
    int nx = x + DXS[d];
    int ny = y + DYS[d];
    if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
    if (map[ny][nx] == '#') continue;
    DFS(map, w, h, nx, ny, visited);
  }
}

bool ProcessCase() {
  int w, h;
  cin >> w >> h;
  if (w == 0 && h== 0) return false;

  vector<vector<char>> map;
  map.assign(h, vector<char>(w, '.'));
  for (int y = 0; y < h; ++y) {
    string row;
    cin >> row;
    for (int x = 0; x < w; ++x) {
      map[y][x] = row[x];
    }
  }

  vector<vector<int>> visited;
  visited.assign(h, vector<int>(w, 0));

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (map[y][x] == '@') {
        DFS(map, w, h, x, y, visited);
      }
    }
  }

  int count = 0;
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (visited[y][x]) ++count;
    }
  }
  cout << count << endl;
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}