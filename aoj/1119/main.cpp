#include <iostream>

using namespace std;

void ProcessCase() {
  int x = 0;
  int y = 0;
  int max_distance_sq;
  int ans_x = 0;
  int ans_y = 0;
  while (true) {
    int dx, dy;
    cin >> dx >> dy;
    if (dx == 0 && dy == 0) {
      break;
    }
    x += dx;
    y += dy;
    if (x * x + y * y > max_distance_sq) {
      ans_x = x;
      ans_y = y;
      max_distance_sq = x * x + y * y;
    } else if (x * x + y * y == max_distance_sq && x > ans_x) {
      ans_x = x;
      ans_y = y;
    }
  }
  cout << ans_x << " " << ans_y << endl;
}

int main() {
  int num_cases;
  cin >> num_cases;
  for (int i = 0; i < num_cases; ++i) ProcessCase();
  return 0;
}