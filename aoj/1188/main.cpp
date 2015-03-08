#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

bool IsNumeric(char c) {
  return '0' <= c && c <= '9';
}

class Parser {
  string str;
  int cur;

  int EvaluateDistrict() {
    assert(str[cur] == '[');
    ++cur;  // Eat '['.
    if (IsNumeric(str[cur])) {
      int value = 0;
      while (IsNumeric(str[cur])) {
        value *= 10;
        value += str[cur] - '0';
        ++cur;
      }
      assert(str[cur] == ']');
      ++cur;  // Eat ']'.
      return value / 2 + 1;
    } else {
      vector<int> children;
      while (true) {
        if (str[cur] == '[') {
          children.push_back(EvaluateDistrict());
        } else if (str[cur] == ']') {
          break;
        } else {
          assert(false);
        }
      }
      ++cur;  // Eat ']'.
      sort(children.begin(), children.end());
      int count = 0;
      for (int i = 0; i < children.size() / 2 + 1; ++i) {
        count += children[i];
      }
      return count;
    }
  }

 public:
  Parser(string& str_in) : str(str_in) {}
  int Evaluate() {
    cur = 0;
    return EvaluateDistrict();
  }
};

void ProcessCase() {
  string input;
  cin >> input;
  Parser parser(input);
  cout << parser.Evaluate() << endl;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) ProcessCase();
  return 0;
}