#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool ProcessCase() {
  string encoded;
  cin >> encoded;
  if (encoded == "#") return false;

  unordered_set<string> curr_set;
  curr_set.insert(encoded);
  unordered_set<string> next_set;

  for (int step = 24; step >= 0; step--) {
    char after = 'a' + step;
    char before = 'a' + step + 1;
    for (const string& curr : curr_set) {
      bool end = false;
      for (int i = 0; i < curr.size(); i++) {
        if (curr[i] == before) {
          end = true;
          break;
        }
        if (curr[i] == after) {
          string next = curr;
          next[i] = before;
          next_set.insert(next);
        }
      }
      if (!end) {
        next_set.insert(curr);
      }
    }

    curr_set.swap(next_set);
    next_set.clear();
  }

  vector<string> answers;
  answers.assign(curr_set.begin(), curr_set.end());
  sort(answers.begin(), answers.end());
  cout << answers.size() << endl;
  if (answers.size() <= 10) {
    for (int i = 0; i < answers.size(); ++i) {
      cout << answers[i] << endl;
    }
  } else {
    for (int i = 0; i < 5; i++) {
      cout << answers[i] << endl;
    }
    for (int i = answers.size() - 5; i < answers.size(); ++i) {
      cout << answers[i] << endl;
    }
  }

  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
