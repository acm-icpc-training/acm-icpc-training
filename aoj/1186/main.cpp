#include <iostream>
 
using namespace std;
 
bool IsSmaller(int h1, int w1, int h2, int w2) {
  int d1 = h1 * h1 + w1 * w1;
  int d2 = h2 * h2 + w2 * w2;
  if (d1 < d2) {
    return true;
  }
  if (d1 > d2) {
    return false;
  }
  return h1 < h2;
}

bool ProcessCase() {
  int input_h, input_w;
  cin >> input_h >> input_w;
  if (input_h == 0 && input_w == 0) {
    return false;
  }
  int ans_h = 149;
  int ans_w = 150;
  for (int h = 1; h <= 150; ++h) {
    for (int w = h + 1; w <= 150; ++w) {
      if (IsSmaller(input_h, input_w, h, w) &&
          IsSmaller(h, w, ans_h, ans_w)) {
        ans_h = h;
        ans_w = w;
      }
    }
  }
  cout << ans_h << " " << ans_w << endl;
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}
