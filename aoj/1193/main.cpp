#include <iostream>
#include <vector>

using namespace std;

void PrintBoard(vector<vector<int>>& board, int h) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < 5; j++) {
      cout << board[i][j];
      if (j < 5) {
        cout << " ";
      }
    }
    cout << endl;
  }
}

int Solve(vector<vector<int>>& board, int h) {
  int ans = 0;
  bool changed = false;
  while (true) {
    for (int row = 0; row < h; row++) {
      for (int col_start = 0; col_start < 5; col_start++) {
        if (board[row][col_start] == 0) {
          continue;
        }

        int col_end = col_start;
        for (int col = col_start + 1; col < 5; col++) {
          if (board[row][col] == board[row][col_start]) {
            col_end = col + 1;
          } else {
            break;
          }
        }
        if (col_end - col_start >= 3) {
          ans += board[row][col_start] * (col_end - col_start);
          for (int col = col_start; col < col_end; col++) {
            board[row][col] = 0;
          }
          changed = true;
        }
      }
    }

    for (int col = 0; col < 5; col++) {
      vector<int> col_stones;
      for (int row = 0; row < h; row++) {
        if (board[row][col] > 0) {
          col_stones.push_back(board[row][col]);
        }
      }
      for (int row = 0; row < h - col_stones.size(); row++) {
        board[row][col] = 0;
      }
      for (int row = h - col_stones.size(); row < h; row++) {
        board[row][col] = col_stones[row - (h - col_stones.size())];
      }
    }

    if (!changed) {
      break;
    } else {
      changed = false;
    }
  }
  return ans;
}

bool ProcessCase() {
  int h;
  cin >> h;
  if (h == 0) return false;
  vector<vector<int>> board;
  board.assign(h, vector<int>(5, 0));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < 5; j++) {
      cin >> board[i][j];
    }
  }
  int ans = Solve(board, h);
  cout << ans << endl;
  return true;
}

int main() {
  while (ProcessCase()) {}
  return 0;
}
