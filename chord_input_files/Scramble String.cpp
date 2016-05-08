// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Scramble String
// Given a string s1, we may represent it as a binary tree by partitioning it to
// two non-empty substrings recursively.

#include "leetcode.h"

class Solution {
  bool isScramble1(string s1, string s2) {
    if (s1.size() != s2.size()) {
      return false;
    }
    return _dfs1(s1.begin(), s2.begin(), s1.size());
  }

  bool _dfs1(string::iterator it1, string::iterator it2, int n) {
    if (n == 0 || n == 1 && *it1 == *it2) {
      return true;
    }
    vector<int> count(256, 0);
    for (int i = 0; i < n; ++i) {
      ++count[*(it1 + i)];
      --count[*(it2 + i)];
    }
    for (auto& it : count) {
      if (it != 0) {
        return false;
      }
    }

    for (int i = 1; i < n; ++i) {
      if (_dfs1(it1, it2, i) && _dfs1(it1 + i, it2 + i, n - i)
        || _dfs1(it1, it2 + (n - i), i) && _dfs1(it1 + i, it2, n - i)) {
        return true;
      }
    }
    return false;
  }

  typedef vector<vector<vector<char>>> VEC3D;

  bool _dfs2(string& s1, string& s2, VEC3D& dp, int i, int j, int len) {
    char& cur = dp[len][i][j];
    if (cur != -1) {
      return dp[len][i][j];
    }
    if (len == 1) {
      return cur = (s1[i] == s2[j]);
    }
    if (len == 0) {
      return cur = true;
    }

    // k cannot equals to the len since there is always a partition point
    for (int k = 1; k < len; ++k) {
      cur = ((_dfs2(s1, s2, dp, i, j, k) && _dfs2(s1, s2, dp, i + k, j + k, len - k))
          || (_dfs2(s1, s2, dp, i, j + len - k, k) && _dfs2(s1, s2, dp, i + k, j, len - k)));
      if (cur) {
        break;
      }
    }

    return cur;
  }

  int isScramble2(string s1, string s2) {
    if (s1.size() != s2.size()) {
      return false;
    }
    int n = s1.size();

    // dp[k][i][j] is ture indicates that s1[i...(i + k - 1)] equals to
    // s2[j...(j + k - 1)]
    VEC3D dp(n + 1, vector<vector<char>>(n, vector<char>(n, -1)));
    return _dfs2(s1, s2, dp, 0, 0, n);

  }

public:
  bool isScramble(string s1, string s2) {
    // return isScramble1(s1, s2);
    return isScramble2(s1, s2);
  }
};

int main() {
  Solution sol;
  bool res = sol.isScramble("aa", "ab");
  cout << res << endl;
  return 0;
}
