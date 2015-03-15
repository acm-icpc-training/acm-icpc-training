#include <cassert>
#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<string, int> atom_to_weight;

class Parser {
  string str;
  int cur;

  bool IsDigit(char c) {
    return '0' <= c && c <= '9';
  }

  bool IsUpperCase(char c) {
    return 'A' <= c && c <= 'Z';
  }

  bool IsLowerCase(char c) {
    return 'a' <= c && c <= 'z';
  }

  int EvaluateMolecule() {
    int weight = 0;
    while (true) {
      weight += EvaluateTerm();
      if (!IsUpperCase(str[cur]) && str[cur] != '(') return weight;
    }
  }

  int EvaluateTerm() {
    if (str[cur] == '(') {
      ++cur;
      int weight = EvaluateMolecule();
      assert(str[cur] == ')');
      ++cur;
      int number = EvaluateNumber();
      return weight * number;
    }
    int atom_weight = EvaluateAtom();
    if (IsDigit(str[cur])) {
      int number = EvaluateNumber();
      return atom_weight * number;
    }
    return atom_weight;
  }

  int EvaluateNumber() {
    int num = 0;
    while (IsDigit(str[cur])) {
      num *= 10;
      num += str[cur] - '0';
      ++cur;
    }
    return num;
  }

  int EvaluateAtom() {
    assert(IsUpperCase(str[cur]));
    if (IsLowerCase(str[cur + 1])) {
      string atom = str.substr(cur, 2);
      cur += 2;
      if (atom_to_weight.find(atom) == atom_to_weight.end()) {
        throw "UNKNOWN";
      }
      return atom_to_weight[atom];
    } else {
      string atom = str.substr(cur, 1);
      ++cur;
      if (atom_to_weight.find(atom) == atom_to_weight.end()) {
        throw "UNKNOWN";
      }
      return atom_to_weight[atom];
    }
  }

 public:
  Parser(string str_in) : str(str_in) {}

  int Evaluate() {
    cur = 0;
    return EvaluateMolecule();
  }
};

int main() {
  // First part.
  while (true) {
    string atom;
    cin >> atom;
    if (atom == "END_OF_FIRST_PART") break;
    int weight;
    cin >> weight;
    atom_to_weight[atom] = weight;
  }

  // Second part.
  while (true) {
    string molecule;
    cin >> molecule;
    if (molecule == "0") break;
    Parser parser(molecule + "$");
    try {
      int weight = parser.Evaluate();
      cout << weight << endl;
    } catch(...) {
      cout << "UNKNOWN" << endl;
    }
  }
  return 0;
}
