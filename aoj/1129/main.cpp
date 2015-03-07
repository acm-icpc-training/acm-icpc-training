#include <iostream>
#include <vector>

using namespace std;

bool ProcessCase() {
  int n, r;
  cin >> n >> r;
  if (n == 0 && r == 0) return false;
  vector<int> cards;
  for (int card_id = n; card_id >= 1; --card_id) {
    cards.push_back(card_id);
  }
  for (int cut_iter = 0; cut_iter < r; ++cut_iter) {
    int p, c;
    cin >> p >> c;
    vector<int> next_cards(cards);
    for (int i = 0; i < c; ++i) {
      next_cards[i] = cards[i + (p - 1)];
    }
    for (int i = 0; i < p - 1; ++i) {
      next_cards[c + i] = cards[i];
    }
    cards.assign(next_cards.begin(), next_cards.end());
  }
  cout << cards[0] << endl;
  return true;
}

int main() {
  while (ProcessCase());
  return 0;
}
