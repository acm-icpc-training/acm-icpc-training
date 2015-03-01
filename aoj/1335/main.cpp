#include <iostream>

using namespace std;

int Count(int n, int k, int s) {
  if (k == 0) {
    if (s == 0) {
      return 1;
    } else {
      return 0;
    }
  }

  int count = 0;
  for (int i = 1; i <= n; ++i) {
    count += Count(i - 1, k - 1, s - i);
  }
  return count;
}

bool ProcessCase() {
  int n, k, s;
  cin >> n >> k >> s;
  if (n == 0 && k == 0 && s == 0) {
    return false;
  }

  cout << Count(n, k, s) << endl;
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}
