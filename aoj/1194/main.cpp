#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits>
#include <vector>
 
using namespace std;
 
const int kOffset = 20;
const int kMaxX = 40;
 
bool ProcessCase() {
  int r, n;
  cin >> r >> n;
  if (r == 0 && n == 0) return false;

  vector<int> heights;
  heights.assign(kMaxX, 0);
  for (int i = 0; i < n; i++) {
    int xl, xr, height;
    cin >> xl >> xr >> height;
    xl += kOffset;
    xr += kOffset;
    for (int x = xl; x < xr; x++) {
      heights[x] = max(height, heights[x]);
    }
  }
  double ans = numeric_limits<double>::max();
  for (int xl = kOffset - r; xl < kOffset + r; xl++) {
    int xr = xl + 1;
    int dl = kOffset - xl;
    int dr = kOffset - xr;
    ans = min(r - sqrt(r * r - dl * dl) + heights[xl], ans);
    ans = min(r - sqrt(r * r - dr * dr) + heights[xl], ans);
  }
  printf("%.6f\n", ans);
  return true;
}

int main() {
  while (ProcessCase()) {}
}
