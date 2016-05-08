// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 11, 2014
// Update:     May 11, 2014
//
// Valid Sudoku
// Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules
// (http://sudoku.com.au/TheRules.aspx).
// The Sudoku board could be partially filled, where empty cells are filled with
// the character '.'.

#include "leetcode.h"

class Solution {
public:
  bool isValidSudoku(vector<vector<char> > &board) {
    int n = 9;
    vector<int> row(n, 0), col(n, 0), block(n, 0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == '.') {
          continue;
        }
        int bit = 1 << (board[i][j] - '1');
        // Check row, col and block
        if (row[i] & bit or col[j] & bit or block[i / 3 * 3 + j / 3] & bit) {
          return false;
        }
        row[i] |= bit;
        col[j] |= bit;
        block[i / 3 * 3 + j / 3] |= bit;
      }
    }
    return true;
  }
};

int main() {
  return 0;
}
