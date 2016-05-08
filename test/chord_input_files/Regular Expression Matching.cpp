// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 30, 2014
// Update:     Aug 02, 2014
//
// Regular Expression Matching
// Implement regular expression matching with support for '.' and '*'.
//
// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.
//
// The matching should cover the entire input string (not partial).
//
// The function prototype should be:
// bool isMatch(const char *s, const char *p)
//
// Some examples:
// isMatch("aa","a") → false
// isMatch("aa","aa") → true
// isMatch("aaa","aa") → false
// isMatch("aa", "a*") → true
// isMatch("aa", ".*") → true
// isMatch("ab", ".*") → true
// isMatch("aab", "c*a*b") → true

#include "leetcode.h"

class Solution {

  bool _dfs(int i, const string& s, int j, const string& p) {
    //printf("i = %d, j = %d\n", i, j);
    int ns = (int)s.size(), np = (int)p.size();

    if (j >= np) {
      return i == ns;
    }

    if (j == np - 1) {
      return (i == ns - 1) && (s[i] == p[j] || p[j] == '.');
    } else if (j + 1 < np) {
      if (p[j + 1] == '*') {
        while (i < ns && (s[i] == p[j] || p[j] == '.')) {
          if (_dfs(i, s, j + 2, p)) {
            return true;
          }
          ++i;
        }
        return _dfs(i, s, j + 2, p);
      } else {
        return (s[i] == p[j] || p[j] == '.') && _dfs(i + 1, s, j + 1, p);
      }
    }

    return false;
  }

  // can not handle the case when there is continuous *
  bool isMatch1(string s, string p) {
    return _dfs(0, s, 0, p);
  }

  bool isMatch2(const char *s, const char *p) {
    int n = strlen(s);
    int m = strlen(p);
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (dp[i][j]) {
          if (i < n && (s[i] == p[j] || p[j] == '.')) {
            dp[i + 1][j + 1] = true;
          }
          if (j + 1 < m && p[j + 1] == '*') {
            dp[i][j + 2] = true;
            for (int k = i; k < n && (p[j] == '.' || p[j] == s[k]); ++k) {
              dp[k + 1][j + 2] = true;
            }
          }
        }
      }
    }

    return dp[n][m];
  }

  bool isMatch3(const char* s, const char* p) {
    int n = strlen(s);
    int m = strlen(p);
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;
    // i should start from 0, to handle following case
    // "abc", "*a*b*cabc"
    for (int i = 0; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (p[j - 1] != '*') {
          if (i - 1 >= 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '.') && dp[i - 1][j - 1]) {
            dp[i][j] = true;
          }
        } else {
          if (j - 2 >= 0 && dp[i][j - 2]) { // ignore * and its previous char
            dp[i][j] = true;
          } else {
            for (int k = i; k >= 1 && (s[k - 1] == p[j - 2] || p[j - 2] == '.'); --k) {
              if (dp[k][j - 1]) {
                dp[i][j] = true;
                break;
              }
            }
          }
        }
      }
    }

    return dp[n][m];
  }

public:
  bool isMatch(string s, string p) {
    return isMatch1(s, p);
    //return isMatch2(s, p);
    //return isMatch3(s, p);
  }
};

int main() {
  //char* s = "abcdeeeek";
  //char* p = "abc.*k";
  char* s = "aa";
  char* p = ".*";

  Solution sol;
  bool res = sol.isMatch(s, p);
  printf("%d\n", res);

  return 0;
}
