#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1000000;

vector<int> is_prime_table;

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
    if (is_prime_table[x]) {
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
  is_prime_table.assign(MAX_N + 1, false);
  for (int i = 1; i <= MAX_N; ++i) {
    is_prime_table[i] = IsPrime(i);
  }
  while (ProcessCase());
  return 0;
}