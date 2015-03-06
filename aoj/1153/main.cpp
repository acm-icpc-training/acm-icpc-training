#include <iostream>
#include <vector>

using namespace std;

bool ProcessCase() {
  int n, m;
  cin >> n >> m;
  if (n == 0 && m ==0) {
    return false;
  }

  vector<int> xs(n, 0), ys(m, 0);
  int xs_sum = 0, ys_sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> xs[i];
    xs_sum += xs[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> ys[i];
    ys_sum += ys[i];
  }

  bool ans_found = false;
  int ans_x = 0;
  int ans_y = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (xs_sum - xs[i] + ys[j] == ys_sum + xs[i] - ys[j]) {
        if (!ans_found) {
          ans_found = true;
          ans_x = xs[i];
          ans_y = ys[j];
        } else if (xs[i] + ys[j] < ans_x + ans_y) {
          ans_x = xs[i];
          ans_y = ys[j];
        }
      }
    }
  }

  if (ans_found) {
    cout << ans_x << " " << ans_y << endl;
  } else {
    cout << -1 << endl;
  }
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}