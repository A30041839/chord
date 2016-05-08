// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 9, 2014
// Update:     May 9, 2014
//
// N-Queens
// The n-queens puzzle is the problem of placing n queens on an n*n chessboacd
// such that no two queens attack each other.
// Given an integer n, return all distinct solutions to the n-queens puzzle.
// Each solution contains a distinct boacd configuration of the n-queens' 
// placement, where 'Q' and '.' both indicate a queen and an empty space 
// respectively.

#include <iostream>
#include <vector>

using namespace std;

class Solution {

  bool is_valid1(vector<int>& hash, int row, int col) {
    for (int i = 0; i < row; ++i) {
      if (hash[i] == col || row - i == abs(hash[i] - col)) {
        return false;
      }
    }

    return true;
  }

  void dfs1(const int& n, vector<vector<string>>& res, vector<string>& sub,
    vector<int>& hash, int row) {
    if (row == n) {
      res.push_back(sub);
      return ;
    }

    for (int col = 0; col < n; ++col) {
      if (is_valid1(hash, row, col)) {
        hash[row] = col;
        string s(n, '.');
        s[col] = 'Q';
        sub.push_back(s);
        dfs1(n, res, sub, hash, row + 1);
        hash[row] = -1;
        sub.pop_back();
      }
    }
  }

  vector<vector<string>> solveNQueens1(int n) {
    vector<vector<string>> res;
    vector<string> sub;
    vector<int> hash(n, -1);

    dfs1(n, res, sub, hash, 0);

    return res;
  }

  // ld: leading diagonal
  // cd: counter diagonal
  void dfs2(const int& n, vector<vector<string>>& res, vector<string>& sub,
    int dep, int row, int ld, int cd) {
    if (dep == n) {
      res.push_back(sub);
      return ;
    }

    int valid = ~(row | cd | ld);
    for (int i = n - 1; i >= 0; --i) { // or from 0 to n - 1
      int pos = 1 << i;
      if (valid & pos) {
        sub[dep][i] = 'Q';
        dfs2(n, res, sub, dep + 1, row | pos, (pos | ld) << 1, (pos | cd) >> 1);
        sub[dep][i] = '.';
      }
    }
  }

  vector<vector<string>> solveNQueens2(int n) {
    vector<vector<string>> res;
    vector<string> sub(n, string(n, '.'));

    dfs2(n, res, sub, 0, 0, 0, 0);

    return res;
  }

public:
  vector<vector<string> > solveNQueens(int n) {
    // return solveNQueens1(n);
    return solveNQueens2(n);
  }
};

int main() {
  return 0;
}
