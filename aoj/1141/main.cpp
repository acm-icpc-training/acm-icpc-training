#include <iostream>
#include <vector>

using namespace std;

bool IsPrime(int x) {
  if (x == 1) return false;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

bool ProcessCase() {
  int a, d, n;
  cin >> a >> d >> n;
  if (a == 0 && d == 0 && n == 0) return false;
  int x = a;
  int count = 0;
  while (true) {
    if (IsPrime(x)) {
      ++count;
    }
    if (count == n) {
      cout << x << endl;
      return true;
    }
    x += d;
  }
}

int main() {
  while (ProcessCase());
  return 0;
}