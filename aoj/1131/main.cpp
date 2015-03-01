#include <iostream>

using namespace std;

int Count(int p, int q, int a, int l, int n) {
  if (p == 0) {
    return 1;
  }
  if (n == 0) {
    return 0;
  }

  int count = 0;
  for (int x = l; x <= a; ++x) {
    int r = p * x - q;
    int s = q * x;
    if (r < 0) {
      continue;
    }
    count += Count(r, s, a / x, x, n - 1);
  }
  return count;
}

bool ProcessCase() {
  int p, q, a, n;
  cin >> p >> q >> a >> n;
  if (p == 0 && q == 0 && a == 0 && n == 0) {
    return false;
  }

  cout << Count(p, q, a, 1, n) << endl;
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}
