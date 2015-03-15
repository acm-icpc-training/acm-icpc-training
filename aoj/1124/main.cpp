#include <iostream>
#include <vector>

using namespace std;

const int MAX_DAY = 100;

bool ProcessCase() {
  int n, q;
  cin >> n >> q;
  if (n == 0 && q == 0) return false;

  vector<int> count(MAX_DAY + 1);
  for (int i = 0; i < n; ++i) {
    int m;
    cin >> m;
    for (int j = 0; j < m; ++j) {
      int date;
      cin >> date;
      ++count[date];
    }
  }

  int ans_date = 0;
  int max_count = 0;
  for (int d = 1; d <= MAX_DAY; ++d) {
    if (count[d] >= q && count[d] > max_count) {
      ans_date = d;
      max_count = count[d];
    }
  }
  cout << ans_date << endl;
  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
