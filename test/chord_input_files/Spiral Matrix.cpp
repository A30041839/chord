// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Spiral Matrix
// Given a matrix of m x n elements (m rows, n columns), return all elements of
// the matrix in spiral order.
// For example,
// Given the following matrix:
// 
// [
//  [ 1, 2, 3 ],
//  [ 4, 5, 6 ],
//  [ 7, 8, 9 ]
// ]
// You should return [1,2,3,6,9,8,7,4,5].

#include "leetcode.h"

class Solution {
public:
  vector<int> spiralOrder(vector<vector<int> > &matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return {};
    }
    int imin = 0, imax = matrix.size() - 1;
    int jmin = 0, jmax = matrix[0].size() - 1;
    vector<int> res;

    while (true) {
      for (int j = jmin; j <= jmax; ++j) {
        res.push_back(matrix[imin][j]);
      }
      if (++imin > imax) {
        break;
      }
      for (int i = imin; i <= imax; ++i) {
        res.push_back(matrix[i][jmax]);
      }
      if (jmin > --jmax) {
        break;
      }
      for (int j = jmax; j >= jmin; --j) {
        res.push_back(matrix[imax][j]);
      }
      if (imin > --imax) {
        break;
      }
      for (int i = imax; i >= imin; --i) {
        res.push_back(matrix[i][jmin]);
      }
      if (++jmin > jmax) {
        break;
      }
    }

    return res;
  }
};

int main() {
  vector<vector<int>> v(4);
  v[0] = {1, 2, 3 ,4};
  v[1] = {5, 6, 7, 8};
  v[2] = {9, 10, 11, 12};
  v[3] = {13, 14, 15, 16};

  Solution sol;
  vector<int> res = sol.spiralOrder(v);
  print_vector(res);

  return 0;
}
