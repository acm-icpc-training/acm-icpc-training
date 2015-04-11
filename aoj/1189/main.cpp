#include <climits>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1000000;

struct Int2D {
  int x;
  int y;
  Int2D(int input_x, int input_y) : x(input_x), y(input_y) {}
};

vector<Int2D> num_to_2d;
vector<int> primes;

void FillNumTo2D() {
  num_to_2d.push_back(Int2D(INT_MAX, INT_MAX));
  num_to_2d.push_back(Int2D(0, 0));
  int x = 0;
  int y = 0;
  int len = 1;
  while (true) {
    // Go right.
    for (int i = 0; i < len; ++i) {
      ++x;
      num_to_2d.push_back(Int2D(x, y));
    }
    // Go up.
    for (int i = 0; i < len; ++i) {
      --y;
      num_to_2d.push_back(Int2D(x, y));
    }

    ++len;

    // Go left.
    for (int i = 0; i < len; ++i) {
      --x;
      num_to_2d.push_back(Int2D(x, y));
    }
    // Go down.
    for (int i = 0; i < len; ++i) {
      ++y;
      num_to_2d.push_back(Int2D(x, y));
    }

    ++len;

    if (num_to_2d.size() >= MAX_N + 1) break;
  }
}

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

bool Process() {
  int m, n;
  cin >> m >> n;
  if (m == 0 && n == 0) return false;

  // Create the map.
  int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
  for (int i = 1; i <= m; ++i) {
    int x = num_to_2d[i].x;
    int y = num_to_2d[i].y;
    min_x = min(x, min_x);
    max_x = max(x, max_x);
    min_y = min(y, min_x);
    max_y = max(y, max_x);
  }
  int width = max_x - min_x + 1;
  int height = max_y - min_y + 1;
  int offset_x = -min_x;
  int offset_y = -min_y;
  vector<vector<bool>> map(height, vector<bool>(width, false));
  for (int prime : primes) {
    if (prime > m) break;
    int prime_x = num_to_2d[prime].x + offset_x;
    int prime_y = num_to_2d[prime].y + offset_y;
    map[prime_y][prime_x] = true;
  }

  vector<vector<int>> dp(height, vector<int>(width, -1));
  int start_x = num_to_2d[n].x + offset_x;
  int start_y = num_to_2d[n].y + offset_y;
  dp[start_y][start_x] = map[start_y][start_x] ? 1 : 0;
  for (int y = 1; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int dx = -1; dx <= 1; ++dx) {
        int px = x + dx;
        if (px < 0 || px >= width) continue;
        if (dp[y - 1][px] >= 0) {
          dp[y][x] = max(
              dp[y - 1][px] + (map[y][x] ? 1 : 0),
              dp[y][x]);
        }
      }
    }
  }

  int max_num_primes = 0;
  int largest_last_prime = 0;
  for (int i = 1; i <= m; ++i) {
    int x = num_to_2d[i].x + offset_x;
    int y = num_to_2d[i].y + offset_y;
    if (!map[y][x]) {
      continue;
    }
    if (dp[y][x] >= 1 && dp[y][x] >= max_num_primes) {
      max_num_primes = dp[y][x];
      largest_last_prime = i;
    }
  }

  cout << max_num_primes << " " << largest_last_prime << endl;

  return true;
}

int main() {
  FillNumTo2D();
  FillPrimes();
  while (Process());
  return 0;
}
