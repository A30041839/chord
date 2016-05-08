// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 18, 2014
// Update:     May 18, 2014
//
// Rotate Image
//You are given an n x n 2D matrix representing an image.
// Rotate the image by 90 degrees (clockwise).

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  // Rotate twice, upside down and rotate with the positive diagonal
  void rotate1(vector<vector<int> > &matrix) {
    int n = matrix.size();
    if (n == 0) {
      return ;
    }

    // Upside down
    for (int i = 0; i < n / 2; ++i) {
      for (int j = 0; j < n; ++j) {
        swap(matrix[i][j], matrix[n - i - 1][j]);
      }
    }

    // Rotate according to the minor diagonal
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        swap(matrix[i][j], matrix[j][i]);
      }
    }
  }

  void rotate2(vector<vector<int> > &matrix) {
    if (matrix.empty()) {
      return ;
    }

    int n = matrix.size();
    for (int layer = 0; layer < n / 2; ++layer) {
      int left = layer, right = n - layer - 1;
      int top = layer, bottom = n - layer - 1;

      for (int col = layer; col < n - layer - 1; ++col) {

        int offset = col - layer;
        int left_top = matrix[top][left + offset];

        // left bottom -> left top
        matrix[top][left + offset] = matrix[bottom - offset][left];

        // right bottom -> left bottom
        matrix[bottom - offset][left] = matrix[bottom][right - offset];

        // right top -> right bottom
        matrix[bottom][right - offset] = matrix[top + offset][right];

        // top left -> right top
        matrix[top + offset][right] = left_top;
      }
    }
  }

public:
  void rotate(vector<vector<int> > &matrix) {
    //rotate1(matrix);
    rotate2(matrix);
  }

};

int main() {
  return 0;
}
