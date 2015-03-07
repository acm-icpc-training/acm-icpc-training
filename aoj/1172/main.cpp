#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 123456;

vector<int> is_prime_table;

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
    if (is_prime_table[i]) {
      ++count;
    }
  }
  cout << count << endl;

  return true;
}

int main() {
  is_prime_table.assign(2 * MAX_N + 1, false);
  for (int i = 1; i <= 2 * MAX_N; ++i) {
    is_prime_table[i] = IsPrime(i);
  }
  while (ProcessCase());
}
