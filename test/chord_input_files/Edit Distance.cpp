// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 22, 2014
// Update:     May 22, 2014
//
// Edit Distance 
// Given two words word1 and word2, find the minimum number of steps required to
// convert word1 to word2. (each operation is counted as 1 step.)
//
// You have the following 3 operations permitted on a word:
// a) Insert a character
// b) Delete a character
// c) Replace a character

#include <iostream>
#include <string>

using namespace std;

class Solution {
  // O(N^2) space
  int minDistance1(string word1, string word2) {
    int n = (int)word1.size();
    int m = (int)word2.size();
    int dp[n + 1][m + 1];

    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
      dp[i][0] = i;
    }
    for (int j = 1; j <= m; ++j) {
      dp[0][j] = j;
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        dp[i][j] = min(dp[i - 1][j - 1] + (word1[i - 1] != word2[j - 1]),
          min(dp[i - 1][j], dp[i][j - 1]) + 1);
      }
    }

    return dp[n][m];
  }

  // O(N) space
  int minDistance2(string word1, string word2) {
    int n = word1.size();
    int m = word2.size();
    int dp[m + 1];

    dp[0] = 0;
    // When n == 0
    for (int i = 1; i <= m; ++i) {
      dp[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
      int leftupper = 0, leftupper_backup = dp[0];
      dp[0] = i;
      for (int j = 1; j <= m; ++j) {
        leftupper = leftupper_backup;
        leftupper_backup = dp[j];
        dp[j] = min(leftupper + (word1[i - 1] != word2[j - 1]),
          min(dp[j - 1], dp[j]) + 1);
      }
    }

    return dp[m];
  }

public:
  int minDistance(string word1, string word2) {
    //return minDistance1(word1, word2);
    return minDistance2(word1, word2);
  }
};

int main() {
  string s1 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef";
  string s2 = "bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg";
  Solution sol;

  int res = sol.minDistance(s1, s2);
  cout << res << endl;

  return 0;
}
