// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 9, 2014
// Update:     May 9, 2014
//
// N-Queens II
// The n-queens puzzle is the problem of placing n queens on an n*n chessboacd
// such that no two queens attack each other.
// Given an integer n, return all distinct solutions to the n-queens puzzle.
// Each solution contains a distinct boacd configuration of the n-queens' 
// placement, where 'Q' and '.' both indicate a queen and an empty space
// respectively.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {

  bool is_valid1(vector<int>& hash, int col, int row) {
    for (int i = 0; i < row; ++i) {
      if (hash[i] == col || row - i == abs(hash[i] - col)) {
        return false;
      }
    }
    return true;
  }

  void dfs1(const int& n, int& res, vector<int>& hash, int row) {
    if (row == n) {
      ++res;
      return ;
    }
    for (int col = 0; col < n; ++col) {
      if (is_valid1(hash, col, row)) {
        hash[row] = col;
        dfs1(n, res, hash, row + 1);
        hash[row] = -1;
      }
    }
  }

  // !! Recursion
  int totalNQueens1(int n) {
    int res = 0;
    vector<int> hash(n, 0);
    dfs1(n, res, hash, 0);
    return res;
  }

  void dfs2(const int& n, int& res, int row, int ld, int cd) {
    if (row == (1 << n) - 1) {
      ++res;
      return ;
    }

    int valid = ~(row | ld | cd);
    for (int i = n - 1; i >= 0; --i) {
      int mask = (1 << i);
      if (valid & mask) {
        // the operation of ld and cd should be taken care of
        // or should be made, then shift
        // the overflow of shift should be noted
        dfs2(n, res, row | mask, (ld | mask) << 1, (cd | mask) >> 1);
      }
    }
  }

  // !! Bit Manipulation, only when n is small
  int totalNQueens2(int n) {
    int res = 0;
    dfs2(n, res, 0, 0, 0);
    return res;
  }

public:
  int totalNQueens(int n) {
    //return totalNQueens1(n);
    return totalNQueens2(n);
  }
};

int main() {
  return 0;
}
