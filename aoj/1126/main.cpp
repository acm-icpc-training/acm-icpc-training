#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsDigit(char c) {
  return '0' <= c && c <= '9';
}

int ParseDigit(char c) {
  return c - '0';
}

bool IsSmaller(const string& s1, const string& s2) {
  if (s1 == "*" && s2 == "*") return false;
  if (s1 == "*" && s2 != "*") return true;
  if (s1 != "*" && s2 == "*") return false;

  if (s1.size() < s2.size()) return true;
  if (s1.size() > s2.size()) return false;
  for (int i = 0; i < s1.size(); ++i) {
    if (s1[i] < s2[i]) return true;
    if (s1[i] > s2[i]) return false;
  }
  return false;
}

bool ProcessCase() {
  int w, h;
  cin >> w >> h;
  if (w == 0 && h == 0) return false;
  vector<string> matrix;
  for (int y = 0; y < h; ++y) {
    string row;
    cin >> row;
    matrix.push_back(row);
  }
  vector<vector<string>> dp(h, vector<string>(w, "*"));
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      char c = matrix[y][x];
      if (!IsDigit(c)) continue;
      dp[y][x] = c;
      if (x >= 1) {
        string left = dp[y][x - 1];
        if (left != "*" && left != "0" && IsSmaller(dp[y][x], left + c)) {
          dp[y][x] = left + c;
        }
      }
      if (y >= 1) {
        string up = dp[y - 1][x];
        if (up != "*" && up != "0" && IsSmaller(dp[y][x], up + c)) {
          dp[y][x] = up + c;
        }
      }
    }
  }
  string ans = "*";
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (IsSmaller(ans, dp[y][x])) ans = dp[y][x];
    }
  }
  cout << ans << endl;
  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
