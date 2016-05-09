// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Word Break
// Given a string s and a dictionary of words dict, determine if s can be 
// segmented into a space-separated sequence of one or more dictionary words.
// For example, given
// s = "leetcode",
// dict = ["leet", "code"].
// Return true because "leetcode" can be segmented as "leet code".

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  bool wordBreak(string s, unordered_set<string> &dict) {
    int n = s.size();
    vector<bool> dp(n, false);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= i; ++j) {
        if ((j == 0 || dp[j - 1]) && dict.count(s.substr(j, i - j + 1))) {
          dp[i] = true;
          break;
        }
      }
    }

    return dp[n - 1];
  }
};

int main() {
  return 0;
}
