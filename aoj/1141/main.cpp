#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1000000;

vector<int> primes;

void FillPrimes() {
  for (int i = 2; i <= MAX_N; ++i) {
    bool is_prime = true;
    for (int k = 0; k < primes.size() && primes[k] * primes[k] <= i; ++k) {
      if (i % primes[k] == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      primes.push_back(i);
    }
  }
}

bool ProcessCase() {
  int a, d, n;
  cin >> a >> d >> n;
  if (a == 0 && d == 0 && n == 0) return false;
  int x = a;
  int count = 0;
  while (true) {
    if (binary_search(primes.begin(), primes.end(), x)) {
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
  FillPrimes();
  while (ProcessCase());
  return 0;
}
