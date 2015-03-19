#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
 
const int MAX_N = 123456;
 
vector<int> primes;
 
void FillPrimes() {
  for (int i = 2; i <= 2 * MAX_N; ++i) {
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
  int n;
  cin >> n;
  if (n == 0) {
    return false;
  }
 
  int count = 0;
  for (int i = n + 1; i <= 2 * n; ++i) {
    if (binary_search(primes.begin(), primes.end(), i)) {
      ++count;
    }
  }
  cout << count << endl;
 
  return true;
}
 
int main() {
  FillPrimes();
  while (ProcessCase());
}