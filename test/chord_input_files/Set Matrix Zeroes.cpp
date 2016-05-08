// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 18, 2014
// Update:     May 18, 2014
//
// Set Matrix Zeroes
// Given a m x n matrix, if an element is 0, set its entire row and column to 0.
// Do it in place.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void setZeroes(vector<vector<int> > &matrix) {
    int n = matrix.size(), m = matrix[0].size();
    bool br = false, bc = false;

    for (int j = 0; j < m && br == false; ++j) {
      if (matrix[0][j] == 0) {
        br = true;
      }
    }
    for (int i = 0; i < n && bc == false; ++i) {
      if (matrix[i][0] == 0) {
        bc = true;
      }
    }

    // Needn't worry that the first row and first column have been changed, they
    // should be.
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (matrix[i][j] == 0) {
          matrix[i][0] = matrix[0][j] = 0;
        }
      }
    }

    // First row and frist column should not been set.
    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        if (matrix[i][0] == 0 || matrix[0][j] == 0) {
          matrix[i][j] = 0;
        }
      }
    }

    if (br) {
      for (int j = 0; j < m; ++j) {
        matrix[0][j] = 0;
      }
    }
    if (bc) {
      for (int i = 0; i < n; ++i) {
        matrix[i][0] = 0;
      }
    }
  }
};

int main() {
  return 0;
}
