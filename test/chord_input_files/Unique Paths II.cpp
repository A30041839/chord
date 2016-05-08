// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     May 13, 2014
//
// Unique Paths II
// Follow up for "Unique Paths":
// Now consider if some obstacles are added to the grids. How many unique paths
// would there be?
// An obstacle and empty space is marked as 1 and 0 respectively in the grid.
// For example,
// There is one obstacle in the middle of a 3x3 grid as illustrated below.
// [
//  [0,0,0],
//  [0,1,0],
//  [0,0,0]
// ]
// The total number of unique paths is 2.
//
// Note:
// m and n will be at most 100.

#include "leetcode.h"

class Solution {
  // dp, space complexity O(N^2)
  int uniquePathsWithObstacles1(vector<vector<int> > &obstacleGrid) {
    if (obstacleGrid.empty() or obstacleGrid[0].empty()) {
      return 0;
    }
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    if (obstacleGrid[0][0] == 1 or obstacleGrid[n - 1][m - 1] == 1) {
      return 0;
    }

    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (obstacleGrid[i][j] == 1) {
          continue;
        } else if (i == 0 and j == 0) {
          dp[i][j] = 1;
        } else {
          dp[i][j] = dp[max(0, i - 1)][j] + dp[i][max(0, j - 1)];
        }
      }
    }

    return dp[n - 1][m - 1];
  }

  // dp, space complexity O(N)
  int uniquePathsWithObstacles2(vector<vector<int> > &obstacleGrid) {
    if (obstacleGrid.empty() or obstacleGrid[0].empty()) {
      return 0;
    }
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    if (obstacleGrid[0][0] == 1 or obstacleGrid[n - 1][m - 1] == 1) {
      return 0;
    }

    vector<int> dp(m, 0);

    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (obstacleGrid[i][j] == 1) {
          dp[j] = 0;
        } else if (j > 0) {
          dp[j] += dp[j - 1];
        }
      }
    }

    return dp[m - 1];
  }
public:
  int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
    return uniquePathsWithObstacles1(obstacleGrid);
    // return uniquePathsWithObstacles2(obstacleGrid);
  }
};

int main() {
  return 0;
}
