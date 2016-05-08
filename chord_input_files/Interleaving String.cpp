// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Interleaving String
// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
//
// For example,
// Given:
// s1 = "aabcc",
// s2 = "dbbca",
//
// When s3 = "aadbbcbcac", return true.
// When s3 = "aadbbbaccc", return false.

#include <iostream>
#include <cstring>

using namespace std;

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    int n1 = s1.size();
    int n2 = s2.size();
    if (n1 + n2 != s3.size()) {
      return false;
    }
    vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));

    for (int i = 0; i <= n1; ++i) {
      for (int j = 0; j <= n2; ++j) {
        if (i == 0 && j == 0) {
          dp[0][0] = true;
          continue;
        }
        if (i > 0 && dp[i - 1][j] && s3[i + j - 1] == s1[i - 1]) {
          dp[i][j] = true;
        }
        if (j > 0 && dp[i][j - 1] && s3[i + j - 1] == s2[j - 1]) {
          dp[i][j] = true;
        }
      }
    }

    return dp[n1][n2];
  }
};

int main() {
  return 0;
}
