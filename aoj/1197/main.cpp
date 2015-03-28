#include <algorithm>
#include <iostream>

using namespace std;

enum Face { BOTTOM, EAST, NORTH, WEST, SOUTH, TOP };

struct Die {
  vector<int> remainings;

  Die(const vector<int> in_remainings) : remainings(in_remainings) {}
  Die(const Die& die) : remainings(die.remainings) {}

  void Rotate(Face f1, Face f2, Face f3, Face f4) {
    int tmp = remainings[f1];
    remainings[f1] = remainings[f2];
    remainings[f2] = remainings[f3];
    remainings[f3] = remainings[f4];
    remainings[f4] = tmp; 
  }

  void RotateEast() {
    Rotate(BOTTOM, EAST, TOP, WEST);
  }

  void RotateNorth() {
    Rotate(BOTTOM, NORTH, TOP, SOUTH);
  }

  void RotateWest() {
    Rotate(BOTTOM, WEST, TOP, EAST);
  }

  void RotateSouth() {
    Rotate(BOTTOM, SOUTH, TOP, NORTH);
  }

  void Rotate(int dir) {
    switch(dir) {
      case 0: RotateEast(); break;
      case 1: RotateNorth(); break;
      case 2: RotateSouth(); break;
      case 3: RotateWest(); break;
    }
  }

  void Decrement() {
    --remainings[BOTTOM];
  }

  bool IsEligible() {
    if (remainings[BOTTOM] < 0) return false;
    int v1 = remainings[BOTTOM] + remainings[TOP];
    int v2 = remainings[EAST] + remainings[WEST];
    int v3 = remainings[NORTH] + remainings[SOUTH];
    if (v1 > v2 + v3) return false;
    if (v2 > v3 + v1 + 1) return false;
    if (v3 > v1 + v2 + 1) return false;
    return true;
  }
};

const string ENSW = "ENSW";

string SolveFixedTargets(const vector<int> targets, const string& curr_best) {
  int sum_targets = accumulate(targets.begin(), targets.end(), 0);

  Die die(targets);
  string res = "";
  bool better = false;
  for (int i = 0; i < sum_targets; ++i) {
    int next_dir = -1;
    for (int dir = 0; dir < 4; ++dir) {
      Die next(die);
      next.Rotate(dir);
      next.Decrement();
      if (next.IsEligible()) {
        next_dir = dir;
        break;
      }
    }
    if (next_dir < 0) return "";
    die.Rotate(next_dir);
    die.Decrement();
    res += ENSW[next_dir];
    if (curr_best != "") {
      if (!better) {
        if (curr_best[i] < res[i]) return "";
        if (curr_best[i] > res[i]) better = true;
      }
    }
  }
  return res;
}

bool ProcessCase() {
  vector<int> targets(6, 0);
  for (int i = 0; i < 6; ++i) {
    cin >> targets[i];
  }
  if (all_of(targets.begin(), targets.end(),
             [](int val) { return val == 0; })) {
    return false;
  }
  int p, q;
  cin >> p >> q;

  sort(targets.begin(), targets.end());
  string ans = "";
  do {
    string candidate = SolveFixedTargets(targets, ans);
    if (candidate == "") continue;
    ans = candidate;
  } while (next_permutation(targets.begin(), targets.end()));

  if (ans == "") cout << "impossible" << endl;
  else cout << ans.substr(p - 1, q - p + 1) << endl;
  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
