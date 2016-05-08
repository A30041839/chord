// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     May 13, 2014
//
// Minimum Path Sum
// Given a m x n grid filled with non-negative numbers, find a path from top left
// to bottom right which minimizes the sum of all numbers along its path.
//
// Note:
// You can only move either down or right at any point in time.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int minPathSum(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }
    int n = grid.size(), m = grid[0].size();
    vector<int> dp(m, 0);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i == 0 and j == 0) {
          dp[0] = grid[0][0];
        } else if (i == 0) {
          dp[j] = grid[i][j] + dp[j - 1];
        } else if (j == 0) {
          dp[j] += grid[i][j];
        } else {
          dp[j] = grid[i][j] + min(dp[j - 1], dp[j]);
        }
      }
    }

    return dp[m - 1];
  }
};

int main() {
  return 0;
}
