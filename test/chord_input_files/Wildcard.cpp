// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 30, 2014
// Update:     Aug 02, 2014
//
// Wildcard Matching
// Implement wildcard pattern matching with support for '?' and '*'.
//
// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).
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
// isMatch("aa", "*") → true
// isMatch("aa", "a*") → true
// isMatch("ab", "?*") → true
// isMatch("aab", "c*a*b") → false

#include "leetcode.h"

class Solution {
  // TLE
  bool isMatch1(const char* s, const char* p) {
    if (*p == '\0') {
      return *s == '\0';
    }

    if (*p != '*') {
      return ((*p == '?' && *s) || *s == *p) && isMatch1(s + 1, p + 1);
    }

    while (*s) {
      if (isMatch1(s, p + 1)) {
        return true;
      }
      ++s;
    }
    return isMatch1(s, p + 1);
  }

  bool isMatch2(string s, string p) {
    int ns = (int)s.size(), np = (int)p.size();
    int ps = 0, pp = 0, spre = -1, ppre = -1;

    while (ps < ns) {
      if (p[pp] == '?' || p[pp] == s[ps]) {
        ++pp;
        ++ps;
      } else {
        if (p[pp] == '*') {
          while (pp < np && p[pp] == '*') {
            ++pp;
          }
          if (pp == np) {
            return true;
          }
          spre = ps;
          ppre = pp;
        } else {
          if (spre != -1) {
            ps = ++spre;
            pp = ppre;
          } else {
            return false;
          }
        }
      }
    }

    while (pp < np && p[pp] == '*') {
      ++pp;
    }
    return ps == ns && pp == np;
  }

  // TLE
  bool isMatch3(const char *s, const char *p) {
    string s1(s), p1(strlen(p), ' ');
    int nstar = 0, m = 0;
    while (*p != '\0') {
      if (*p != '*' || (*p == '*' && (p1.empty() || p1.back() != *p))) {
        p1[m++] = *p;
        ++nstar;
      }
      ++p;
    }
    p1.resize(m);
    int n = s1.size();
    if (m - nstar > n) {
      return false;
    }
    bool dp[2][m + 1];

    memset(dp, false, sizeof(dp));
    dp[0][0] = true;
    int which = 0;
    for (int i = 0; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (p1[j - 1] != '*') {
          if (i > 1 && (s1[i - 1] == p1[j - 1] || p1[j - 1] == '?') && dp[which ^ 1][j - 1]) {
            dp[which][j] = true;
          }
        } else {
          if (dp[which][j - 1] || i > 1 && dp[which ^ 1][j]) {
            dp[which][j] = true;
          }
        }
      }
      which ^= 1;
    }
    return dp[which ^ 1][m];
  }

public:
  bool isMatch(string s, string p) {
    //return isMatch1(s, p);
    return isMatch2(s, p);
    //return isMatch3(s, p);
  }
};

int main() {
  Solution sol;
  char* s = "c";
  char* p = "*?*";
  bool res = sol.isMatch(s, p);
  cout << res << endl;

  return 0;
}
