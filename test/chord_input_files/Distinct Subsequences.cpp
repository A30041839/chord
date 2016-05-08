// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Distinct Subsequences
// Given a string S and a string T, count the number of distinct subsequences of
// T in S.
//
// A subsequence of a string is a new string which is formed from the original
// string by deleting some (can be none) of the characters without disturbing
// the relative positions of the remaining characters. (ie, "ACE" is a
// subsequence of "ABCDE" while "AEC" is not).
//
// Here is an example:
// S = "rabbbit", T = "rabbit"
// Return 3.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int numDistinct(string S, string T) {
    int sn = S.size();
    int tn = T.size();
    if (tn > sn) {
      return 0;
    }

    // m >= n
    vector<vector<int>> dp(tn + 1, vector<int>(sn + 1, 0));

    for (int i = 0; i <= sn; ++i) {
      dp[0][i] = 1;
    }
    for (int i = 1; i <= tn; ++i) {
      for (int j = i; j <= sn; ++j) {
        dp[i][j] = dp[i][j - 1];
        if (T[i - 1] == S[j - 1]) {
          dp[i][j] += dp[i - 1][j - 1];
        }
        //printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
      }
    }

    return dp[tn][sn];
  }
};

int main() {
  string S = "BABBB";
  string T = "AB";
  Solution sol;

  int res = sol.numDistinct(S, T);
  cout << res << endl;

  return 0;
}
