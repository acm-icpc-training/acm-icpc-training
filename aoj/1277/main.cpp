#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

bool ProcessCase() {
  int n, num_turns, num_loses, num_backs;
  cin >> n >> num_turns >> num_loses >> num_backs;
  if (n == 0 && num_turns == 0 && num_loses == 0 && num_backs == 0) {
    return false;
  }

  vector<bool> is_lose(n + 1, false);
  for (int i = 0; i < num_loses; ++i) {
    int s; cin >> s;
    is_lose[s] = true;
  }
  vector<bool> is_back(n + 1, false);
  for (int i = 0; i < num_backs; ++i) {
    int s; cin >> s;
    is_back[s] = true;
  }

  vector<vector<double>> dp(num_turns + 1, vector<double>(n + 1, 0.0));
  dp[0][0] = 1.0;
  for (int turn = 0; turn < num_turns; ++turn) {
    for (int s = 0; s < n; ++s) {
      int next_turn = turn + 1;
      if (is_lose[s]) {
        if (turn + 2 <= num_turns) {
          next_turn = turn + 2;
        } else {
          continue;
        }
      }

      for (int d = 1; d <= 6; ++d) {
        int t = s + d;
        if (t > n) {
          t = n - (t - n);
        }
        if (is_back[t]) {
          dp[next_turn][0] += dp[turn][s] / 6.0;
        } else {
          dp[next_turn][t] += dp[turn][s] / 6.0;
        }
      }
    }
  }

  double ans = 0.0;
  for (int turn = 1; turn <= num_turns; ++turn) {
    ans += dp[turn][n];
  }
  printf("%.6f\n", ans);

  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
