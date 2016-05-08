// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Word Search
// Given a 2D board and a word, find if the word exists in the grid.
// The word can be constructed from letters of sequentially adjacent cell, where
// "adjacent" cells are those horizontally or vertically neighboring. The same 
// letter cell may not be used more than once.
// 
// For example,
// Given board =
// [
//   ["ABCE"],
//   ["SFCS"],
//   ["ADEE"]
// ]
// word = "ABCCED", -> returns true,
// word = "SEE", -> returns true,
// word = "ABCB", -> returns false.

#include "leetcode.h"

const vector<int> dx = {-1, 1, 0, 0};
const vector<int> dy = {0, 0, 1, -1};

class Solution {
  bool inside(int x, int y, int n, int m) {
    return x >= 0 && x < n && m >= 0 && y < m;
  }

  bool _exist(const string& word, vector<vector<char>>& board, int sx, int sy,
    int n, int m, vector<vector<bool>>& visit, int dep) {
    if (dep == word.size()) {
      return true;
    }
    for (int i = 0; i < 4; ++i) {
      int nx = sx + dx[i];
      int ny = sy + dy[i];
      if (inside(nx, ny, n, m) && board[nx][ny] == word[dep] && visit[nx][ny] == false) {
        visit[nx][ny] = true;
        if (_exist(word, board, nx, ny, n, m, visit, dep + 1)) {
          return true;
        }
        visit[nx][ny] = false;
      }
    }

    return false;
  }

public:
  bool exist(vector<vector<char> > &board, string word) {
    if (board.empty()) {
      return word.empty();
    }

    int n = board.size(), m = board[0].size();
    vector<vector<bool>> visit;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] == word[0]) {
          visit.assign(n, vector<bool>(m, false));
          visit[i][j] = true;
          if (_exist(word, board, i, j, n, m, visit, 1)) {
            return true;
          }
        }
      }
    }

    return false;
  }
};

int main() {
  return 0;
}
