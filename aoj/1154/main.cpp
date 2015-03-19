#include <iostream>
#include <vector>

using namespace std;

vector<int> ms_primes;

bool ProcessCase() {
  int n;
  cin >> n;
  if (n == 1) {
    return false;
  }
  int a = n;
  vector<int> factors;
  for (const int& ms_prime : ms_primes) {
    if (a % ms_prime == 0) {
      factors.push_back(ms_prime);
    }
  }

  cout << n << ":";
  for (const int& factor : factors) {
    cout << " " << factor;
  }
  cout << endl;

  return true;
}

void MakeMSPrimesVector() {
  for (int x = 2; x <= 300000; ++x) {
    if (x % 7 != 1 && x % 7 != 6) {
      continue;
    }
    bool is_ms_prime = true;
    for (int i = 0;
         i < ms_primes.size() && ms_primes[i] * ms_primes[i] <= x;
         ++i) {
      if (x % ms_primes[i] == 0) {
        is_ms_prime = false;
        break;
      }
    }
    if (is_ms_prime) ms_primes.push_back(x);
  }
}

int main() {
  MakeMSPrimesVector();
  while (ProcessCase());
  return 0;
}
