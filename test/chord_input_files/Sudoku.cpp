// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     Jul 23, 2014
//
// Sudoku Solver
// Write a program to solve a Sudoku puzzle by filling the empty cells.
// Empty cells are indicated by the character '.'.
// You may assume that there will be only one unique solution.

#include "leetcode.h"

class Solution {
  static const int N = 9;
  vector<int> row, col, block;

  bool is_valid(int i, int j, int val) {
    return ! ((row[i] & val) || (col[j] & val) || (block[i / 3 * 3 + j / 3] & val));
  }

  bool dfs(vector<vector<char>>& board, vector<pair<int, int>>& empty, int dep) {
    if (dep == empty.size()) {
      return true;
    }

    for (int dig = 0; dig < N; ++dig) {
      int i = empty[dep].first, j = empty[dep].second;
      int val = 1 << dig;
      if (is_valid(i, j, val)) {
        board[i][j] = dig + '1';
        row[i] |= val;
        col[j] |= val;
        block[i / 3 * 3 + j / 3] |= val;
        if (dfs(board, empty, dep + 1)) {
          return true;
        }
        row[i] ^= val;
        col[j] ^= val;
        block[i / 3 * 3 + j / 3] ^= val;
      }
    }
    return false;
  }

public:
  void solveSudoku(vector<vector<char>> &board) {
    vector<pair<int, int>> empty;

    row.assign(N, 0);
    col.assign(N, 0);
    block.assign(N, 0);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (board[i][j] == '.') {
          empty.push_back({i, j});
        } else {
          int val = 1 << (board[i][j] - '1');
          row[i] |= val;
          col[j] |= val;
          block[i / 3 * 3 + j / 3] |= val;
        }
      }
    }

    dfs(board, empty, 0);
  }
};


int main() {
  return 0;
}
