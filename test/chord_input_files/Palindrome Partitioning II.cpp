// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     Jun 12, 2014
//
//Palindrome Partitioning II
// Given a string s, partition s such that every substring of the partition is a
// palindrome.
// Return the minimum cuts needed for a palindrome partitioning of s.
//
// For example, given s = "aab",
// Return 1 since the palindrome partitioning ["aa","b"] could be produced using
// 1 cut.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  int minCut1(string s) {
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
      dp[i][i] = true;
    }
    for (int len = 2; len <= n; ++len) {
      for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;
        if (len == 2) {
          dp[i][j] = s[i] == s[j];
        } else {
          dp[i][j] = (dp[i + 1][j - 1]) && (s[i] == s[j]);
        }
      }
    }

    vector<int> cut(n, n);
    for (int i = 0; i < n; ++i) {
      if (dp[0][i]) {
        cut[i] = 1;
        continue;
      }
      for (int j = 1; j <= i; ++j) {
        if (dp[j][i] && cut[j - 1] + 1 < cut[i]) {
          cut[i] = cut[j - 1] + 1;
        }
      }
    }

    return cut[n - 1] - 1;
  }

  // O(N) space
  int minCut2(string s) {
    int n = s.size();
    vector<int> dp(n, 0);
    vector<bool> is_palind(n, false);

    is_palind[0] = true;
    for (int i = 1; i < n; ++i) {
      dp[i] = dp[i - 1] + 1;
      is_palind[i] = true;
      for (int j = 0; j < i; ++j) {
        is_palind[j] = (s[i] == s[j]) && is_palind[j + 1];
        if (is_palind[j]) {
          dp[i] = j == 0 ? 0 : min(dp[i], dp[j - 1] + 1);
        }
      }
    }

    return dp[n - 1];
  }

public:
  int minCut(string s) {
    //return minCut1(s);
    return minCut2(s);
  }
};

int main() {
  return 0;
}
