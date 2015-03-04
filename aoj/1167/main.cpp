#include <climits>
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 1100000;

int main() {
  vector<int> required_tetrahedral(SIZE, INT_MAX);
  vector<int> required_odd_tetrahedral(SIZE, INT_MAX);
  required_tetrahedral[0] = 0;
  required_odd_tetrahedral[0] = 0;
  for (int i = 1; i < SIZE; ++i) {
    for (int k = 1; k * (k + 1) * (k + 2) / 6 <= i; ++k) {
      int tetrahedral = k * (k + 1) * (k + 2) / 6;
      required_tetrahedral[i] = min(
          required_tetrahedral[i - tetrahedral] + 1,
          required_tetrahedral[i]);
      if (tetrahedral % 2 == 1) {
        required_odd_tetrahedral[i] = min(
            required_odd_tetrahedral[i - tetrahedral] + 1,
            required_odd_tetrahedral[i]);
      }
    }
  }

  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    cout << required_tetrahedral[n] << " " << required_odd_tetrahedral[n]
         << endl;
  }

  return 0;
}
