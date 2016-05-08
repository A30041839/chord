// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Spiral Matrix II 
// Given an integer n, generate a square matrix filled with elements from 1 to
// n^2 in spiral order.
// For example,
// Given n = 3,
// 
// You should return the following matrix:
// [
//  [ 1, 2, 3 ],
//  [ 8, 9, 4 ],
//  [ 7, 6, 5 ]
// ]

#include "leetcode.h"

class Solution {
public:
  vector<vector<int> > generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n));
    int imin = 0, imax = n - 1;
    int jmin = 0, jmax = n - 1;

    int m = 1;
    while (true) {
      for (int j = jmin; j <= jmax; ++j) {
        res[imin][j] = m++;
      }
      if (++imin > imax) {
        break;
      }
      for (int i = imin; i <= imax; ++i) {
        res[i][jmax] = m++;
      }
      if (jmin > --jmax) {
        break;
      }
      for (int j = jmax; j >= jmin; --j) {
        res[imax][j] = m++;
      }
      if (imin > --imax) {
        break;
      }
      for (int i = imax; i >= imin; --i) {
        res[i][jmin] = m++;
      }
      if (++jmin > jmax) {
        break;
      }
    }

    return res;
  }
};

int main() {
  return 0;
}
