#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

bool ProcessCase() {
  string original;
  cin >> original;
  unordered_set<string> created;
  created.insert(original);
  for (int len = 1 ; len <= original.size() - 1; ++len) {
    string first = original.substr(0, len);
    string second = original.substr(len, original.size() - len);
    string first_reversed(first);
    reverse(first_reversed.begin(), first_reversed.end());
    string second_reversed(second);
    reverse(second_reversed.begin(), second_reversed.end());
    created.insert(first + second_reversed);
    created.insert(first_reversed + second);
    created.insert(first_reversed + second_reversed);
    created.insert(second + first);
    created.insert(second + first_reversed);
    created.insert(second_reversed + first);
    created.insert(second_reversed + first_reversed);
  }
  cout << created.size() << endl;
}

int main() {
  int num_cases;
  cin >> num_cases;
  for (int i = 0; i < num_cases; ++i) ProcessCase();
  return 0;
}