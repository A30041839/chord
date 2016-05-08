// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 9, 2014
// Update:     Jul 2, 2014
//
// Search a 2D Matrix
// Write an efficient algorithm that searches for a value in an m x n matrix.
// This matrix has the following properties:
//
// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the previous
// row.
// For example,
//
// Consider the following matrix:
//
// [
//    [1,   3,  5,  7],
//    [10, 11, 16, 20],
//    [23, 30, 34, 50]
// ]
// Given target = 3, return true.

#include "leetcode.h"

class Solution {
  int _lower_bound(vector<int>& num, int target) {
    int start = -1;
    int end = num.size();

    while (end - start > 1) {
      int mid = start  + (end - start) / 2;
      if (num[mid] >= target) {
        end = mid;
      } else {
        start = mid;
      }
    }

    return end;
  }

  int _upper_bound(vector<int>& num, int target) {
    int start = -1;
    int end = num.size();
    // invariant relation is num[start] <= target < num[end]
    while (end - start > 1) {
      int mid = start + (end - start) / 2;
      if (num[mid] > target) {
        end = mid;
      } else {
        start = mid;
      }
    }
    return end;
  }

  bool searchMatrix1(vector<vector<int> > &matrix, int target) {
    int n = matrix.size();
    if (n == 0) {
      return false;
    }
    int m = matrix[0].size();
    vector<int> first_col(n, 0);

    for (int i = 0; i < n; ++i) {
      first_col[i] = matrix[i][0];
    }
    int row = _upper_bound(first_col, target);
    if (row == 0) {
      return false;
    }
    --row;
    int col = _upper_bound(matrix[row], target);
    return col && matrix[row][col - 1] == target;
  }

  bool searchMatrix2(vector<vector<int> > &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
      return false;
    }
    int n = matrix.size(), m = matrix[0].size();
    vector<int> num(n, 0);

    for (int i = 0; i < n; ++i) {
      num[i] = matrix[i][0];
    }
    int row = _lower_bound(num, target);
    if (row >= 0 && row < n && matrix[row][0] == target) {
      return true;
    }
    if (row == 0) {
      return false;
    }
    int col = _lower_bound(matrix[row - 1], target);
    return col != m && matrix[row - 1][col] == target;
  }

  bool searchMatrix3(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
      return false;
    }
    int n = matrix.size(), m = matrix[0].size();
    int start = -1;
    int end = n * m;

    while (end - start > 1) {
      int mid = start + (end - start) / 2;
      int x = mid / m;
      int y = mid % m;

      if (matrix[x][y] >= target) {
        end = mid;
      } else {
        start = mid;
      }
    }
    return end < n * m && matrix[end / m][end % m] == target;
  }

public:
  bool searchMatrix(vector<vector<int> > &matrix, int target) {
    //return searchMatrix1(matrix, target);
    //return searchMatrix2(matrix, target);
    return searchMatrix3(matrix, target);
  }
};

int main() {
  return 0;
}
