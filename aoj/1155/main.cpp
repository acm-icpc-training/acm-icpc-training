#include <cstdlib>
#include <iostream>

using namespace std;

int Negate(int value) {
  return 2 - value;
}

int Conjunction(int v1, int v2) {
  return min(v1, v2);
}

int Disjunction(int v1, int v2) {
  return max(v1, v2);
}

class Parser {
  string str;
  int p, q, r;
  int cur;

  int EvaluateFormula() {
    char c = str[cur];
    if ('0' <= c && c <= '2') {
      ++cur;
      return c - '0';
    } else if (c == 'P') {
      ++cur;
      return p;
    } else if (c == 'Q') {
      ++cur;
      return q;
    } else if (c == 'R') {
      ++cur;
      return r;
    } else if (c == '-') {
      ++cur;
      int value = EvaluateFormula();
      return Negate(value);
    } else if (c == '(') {
      ++cur;
      int value1 = EvaluateFormula();
      char op = str[cur];
      ++cur;
      int value2 = EvaluateFormula();
      if (str[cur] == ')') {
        ++cur;  // Consume ')'.
      } else {
        cerr << "Expected ')' but found '" << str[cur] << "'." << endl;
        exit(1);
      }
      if (op == '*') {
        return Conjunction(value1, value2);
      } else if (op == '+') {
        return Disjunction(value1, value2);
      } else {
        cerr << "Unexpected operator '" << op << "'." << endl;
        exit(1);
      }
    } else {
      cerr << "Unexpected character '" << c << "'." << endl;
      exit(1);
    }
  }

 public:
  Parser(string str_in, int p_in, int q_in, int r_in) :
      str(str_in), p(p_in), q(q_in), r(r_in) {}

  int Evaluate() {
    cur = 0;
    return EvaluateFormula();
  }
};

bool ProcessCase() {
  string input;
  cin >> input;
  if (input == ".") return false;

  input += "$";
  int count = 0;
  for (int p = 0; p <= 2; ++p) {
    for (int q = 0; q <= 2; ++q) {
      for (int r = 0; r <= 2; ++r) {
        Parser parser(input, p, q, r);
        if (parser.Evaluate() == 2) {
          ++count;
        }
      }
    }
  }
  cout << count << endl;
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}
