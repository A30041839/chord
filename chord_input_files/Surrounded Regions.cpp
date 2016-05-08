// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 17, 2014
//
// Surrounded Regions
// Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
// A region is captured by flipping all 'O's into 'X's in that surrounded region .
// For example,
// X X X X
// X O O X
// X X O X
// X O X X
// After running your function, the board should be:
// X X X X
// X X X X
// X X X X
// X O X X

#include "leetcode.h"

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

class Solution {
  queue<pair<int, int>> q;

  bool inside(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
  }

  // NOT used.
  void dfs(int x, int y, int n, int m, vector<vector<char>>& board) {
    board[x][y] = '#';
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (inside(nx, ny, n, m) && board[nx][ny] == 'O') {
        dfs(nx, ny, n, m, board);
      }
    }
  }

  void bfs(int n, int m, vector<vector<char>>& board) {
    while (!q.empty()) {
      int x = get<0>(q.front());
      int y = get<1>(q.front());
      q.pop();
      board[x][y] = '#';

      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (inside(nx, ny, n, m) && board[nx][ny] == 'O') {
          q.push({nx, ny});
        }
      }
    }
  }

public:
  void solve(vector<vector<char>> &board) {
    int n = (int)board.size();

    if (n == 0) {
      return ;
    }

    int m = (int)board[0].size();

    while (!q.empty()) {
      q.pop();
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
          if (board[i][j] == 'O') {
            q.push({i, j});
          }
        }
      }
    }
    bfs(n, m, board);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] == 'O') {
          board[i][j] = 'X';
        } else if (board[i][j] == '#') {
          board[i][j] = 'O';
        }
      }
    }
  }
};

int main() {
  vector<vector<char>> v(4);
  v[0] = {'X', 'X', 'X', 'X'};
  v[1] = {'X', 'O', 'O', 'X'};
  v[2] = {'X', 'X', 'O', 'X'};
  v[3] = {'X', 'O', 'X', 'X'};

  Solution sol;
  sol.solve(v);
  for (auto& s : v) {
    for (auto& c : s) {
      cout << c;
    }
    cout << endl;
  }

  return 0;
}
