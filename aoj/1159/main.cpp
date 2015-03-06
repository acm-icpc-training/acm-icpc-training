#include <iostream>
#include <vector>

using namespace std;

bool ProcessCase() {
  int n, p;
  cin >> n >> p;
  if (n == 0 && p == 0) {
    return false;
  }
  vector<int> candidates(n, 0);
  int bowl = p;
  while (true) {
    for (int i = 0; i < n; ++i) {
      if (bowl == 0) {
        bowl = candidates[i];
        candidates[i] = 0;
      } else {
        --bowl;
        ++candidates[i];
        if (candidates[i] == p) {
          cout << i << endl;
          return true;
        }
      }
    }
  }
}

int main() {
  while (ProcessCase());
  return 0;
}
