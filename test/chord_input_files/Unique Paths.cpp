// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 12, 2014
// Update:     May 12, 2014
//
// Unique Paths
// A robot is located at the top-left corner of a m x n grid.
// The robot can only move either down or right at any point in time. The robot
// is trying to reach
// the bottom-right corner of the grid (marked 'Finish' in the diagram below).
// How many possible unique paths are there?

#include "leetcode.h"

class Solution {
  // dp, space complexity O(N^2)
  int uniquePaths1(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == 0 or j == 0) {
          dp[i][j] = 1;
        } else {
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
      }
    }

    return dp[m - 1][n - 1];
  }

  // dp, space complexity O(N)
  int uniquePaths2(int m, int n) {
    vector<int> dp(n, 0);

    dp[0] = 1;
    for (int i = 0; i < m; ++i) {
      for (int j = 1; j < n; ++j) { // !!
        dp[j] += dp[j - 1];
      }
    }

    return dp[n - 1];
  }

  // combination, C(n + m - 2, m - 1)
  int uniquePaths3(int m, int n) {
    if (m > n) {
      swap(n, m);
    }
    n = m + n - 2;
    --m;
    // The answer is C(n, m)
    // For combination C(n, r), n must be > or = r
    // C(0, 0) = 1
    vector<vector<int>> comb(n + 1, vector<int>(m + 1, 0));

    comb[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
      comb[i][0] = 1;
      for (int j = 1; j <= m; ++j) {
        comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
      }
    }

    return comb[n][m];
  }

  // math, C(n + m - 2, m - 1)
  int uniquePaths4(int m, int n) {
    if (m > n) {
      swap(m, n);
    }
    long long res = 1;
    for (int i = 1; i < m; ++i) {
      // res *= (n + m - 1 - i) / i
      // will cause overflow
      res = res * (n + m - 1 - i) / i;
    }

    return res;
  }

public:
  int uniquePaths(int m, int n) {
    //return uniquePaths1(m, n);
    //return uniquePaths2(m, n);
    //return uniquePaths3(m, n);
    return uniquePaths4(m, n);
  }
};

int main() {
  return 0;
}
