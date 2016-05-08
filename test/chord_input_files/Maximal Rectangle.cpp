// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Maximal Rectangle
// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
// containing all ones and return its area.

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  int larget_area(vector<int>& height) {
    int n = height.size();
    vector<int> width(n, 0);
    stack<int> stk;
    int res = 0;

    for (int i = 0; i < n; ++i) {
      while (!stk.empty() && height[stk.top()] >= height[i]) { // >=
        stk.pop();
      }
      width[i] = stk.empty() ? i + 1 : i - stk.top();
      stk.push(i);
    }

    while (!stk.empty()) {
      stk.pop();
    }

    for (int i = n - 1; i >= 0; --i) {
      while (!stk.empty() && height[stk.top()] >= height[i]) { // >=
        stk.pop();
      }
      width[i] += stk.empty() ? n - i : stk.top() - i;
      --width[i];
      res = max(res, width[i] * height[i]);

      stk.push(i);
    }

    return res;

  }
public:
  int maximalRectangle(vector<vector<char> > &matrix) {
    if (matrix.empty()) {
      return 0;
    }
    int n = matrix.size(), m = matrix[0].size();
    vector<int> h(m, 0);
    int res = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        h[j] = matrix[i][j] == '1' ? h[j] + 1 : 0;
      }
      res = max(res, larget_area(h));
    }

    return res;
  }
};

int main() {
  vector<vector<char>> matrix = {{'0', '1'}, {'1', '0'}};
  Solution sol;
  int res = sol.maximalRectangle(matrix);
  cout << res << endl;

  return 0;
}
