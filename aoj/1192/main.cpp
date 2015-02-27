#include <iostream>
 
using namespace std;
 
bool ProcessCase() {
  int x, y, s;
  cin >> x >> y >> s;
  if (x == 0 && y == 0 && s == 0) {
    return false;
  }

  int ans = 0;
  for (int p1 = 1; p1 <= s - 1; ++p1) {
    for (int p2 = 1; p2 <= s - 1; ++p2) {
      int q1 = p1 * (100 + x) / 100;
      int q2 = p2 * (100 + x) / 100;
      if (q1 + q2 == s) {
        int r1 = p1 * (100 + y) / 100;
        int r2 = p2 * (100 + y) / 100;
        ans = max(r1 + r2, ans);
      }
    }
  }
 
  cout << ans << endl;
  return true;
}

int main() {
  while (ProcessCase());
}
