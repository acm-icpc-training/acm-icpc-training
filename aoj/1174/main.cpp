#include <iostream>
#include <vector>

using namespace std;

const int DXS[] = {1, 0, -1, 0};
const int DYS[] = {0, 1, 0, -1};

class Main {
  int h, w, c;
  vector<vector<int>> initial_board;

  void DFS(const vector<vector<int>>& board, int x, int y,
           vector<vector<bool>>* visited) {
    if ((*visited)[y][x]) {
      return;
    }
    (*visited)[y][x] = true;
    for (int d = 0; d < 4; ++d) {
      int nx = x + DXS[d];
      int ny = y + DYS[d];
      if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
      if (board[ny][nx] != board[0][0]) continue;
      DFS(board, nx, ny, visited);
    }
  }

  vector<vector<bool>> GetConnected(const vector<vector<int>>& board) {
    vector<vector<bool>> connected;
    connected.assign(h, vector<bool>(w, false));
    DFS(board, 0, 0, &connected);
    return connected;
  }

  vector<vector<int>> ChangeColor(const vector<vector<int>>& board, int color) {
    const auto& connected = GetConnected(board);
    vector<vector<int>> next_board(board);
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        if (connected[y][x]) {
          next_board[y][x] = color;
        }
      }
    }
    return next_board;
  }

  int CountConnected(const vector<vector<int>>& board) {
    const auto& connected = GetConnected(board);
    int count = 0;
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        if (connected[y][x]) ++count;
      }
    }
    return count;
  }

  int FindMax(const vector<vector<int>>& board, int remaining_changes) {
    if (remaining_changes == 0) {
      if (board[0][0] != c) {
        cerr << "This should not happen!" << endl;
        return 0;
      }
      return CountConnected(board);
    }
    int ret = 0;
    for (int color = 1; color <= 6; ++color) {
      if (remaining_changes == 1 && color != c) {
        continue;
      }
      const auto& next_board = ChangeColor(board, color);
      ret = max(ret, FindMax(next_board, remaining_changes - 1));
    }
    return ret;
  }

 public:
  bool ProcessCase() {
    cin >> h >> w >> c;
    if (h == 0 && w == 0 && c == 0) {
      return false;
    }

    initial_board.assign(h, vector<int>(w, 0));
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        cin >> initial_board[y][x];
      }
    }
    cout << FindMax(initial_board, 5) << endl;
    return true;
  }
};

int main() {
  while (Main().ProcessCase());
  return 0;
}
