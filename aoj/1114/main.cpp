#include <iostream>
#include <vector>

using namespace std;

void ProcessCase() {
  vector<vector<int>> map(5, vector<int>(5, 0));
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 5; ++x) {
      cin >> map[y][x];
    }
  }
  int ans = 0;
  for (int iy = 0; iy < 5; ++iy) {
    for (int ix = 0; ix < 5; ++ix) {
      for (int h = 1; h <= 5 - iy; ++h) {
        for (int w = 1; w <= 5 - ix; ++w) {
          bool valid = true;
          for (int py = iy; py < iy + h; ++py) {
            for (int px = ix; px < ix + w; ++px) {
              if (!map[py][px]) {
                valid = false;
              }
            }
          }
          if (valid) {
            ans = max(h * w, ans);
          }
        }
      }
    }
  }
  cout << ans << endl;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) ProcessCase();
  return 0;
}