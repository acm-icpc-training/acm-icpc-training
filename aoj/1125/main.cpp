#include <iostream>
#include <vector>

using namespace std;

bool ProcessCase() {
  int n;
  cin >> n;
  if (n == 0) return false;
  int w, h;
  cin >> w >> h;
  vector<vector<int>> map(h, vector<int>(w, 0));
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y; --x; --y;
    map[y][x] = 1;
  }
  int s, t;
  cin >> s >> t;
  int ans = 0;
  for (int py = 0; py <= h - t; ++py) {
    for (int px = 0; px <= w - s; ++px) {
      int count = 0;
      for (int qy = py; qy < py + t; ++qy) {
        for (int qx = px; qx < px + s; ++qx) {
          if (map[qy][qx]) ++count;
        }
      }
      ans = max(count, ans);
    }
  }
  cout << ans << endl;
  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
