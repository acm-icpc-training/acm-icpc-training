#include <iostream>

using namespace std;

bool IsPrime(int x) {
  if (x == 1) return false;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) return false;
  }
  return true;
}

bool ProcessCase() {
  int n;
  cin >> n;
  if (n == 0) {
    return false;
  }

  int count = 0;
  for (int i = n + 1; i <= 2 * n; ++i) {
    if (IsPrime(i)) {
      ++count;
    }
  }
  cout << count << endl;

  return true;
}

int main() {
  while (ProcessCase());
}
