// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 22, 2014
// Update:     May 22, 2014
//
// Word Break II
// Given a string s and a dictionary of words dict, add spaces in s to construct
// a sentence where each word is a valid dictionary word.
// Return all such possible sentences.
//
// For example, given
// s = "catsanddog",
// dict = ["cat", "cats", "and", "sand", "dog"].
// A solution is ["cats and dog", "cat sand dog"].

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
  void dfs(string& s, vector<vector<int>>& dp, vector<string>& res,
    string sub, int pos) {
    if (pos < 0) {
      res.push_back(sub.erase(sub.size() - 1));
      return ;
    }

    for (int pre : dp[pos]) {
      string word = s.substr(pre, pos - pre + 1);
      dfs(s, dp, res, word + " " + sub, pre - 1);
    }
  }

public:
  vector<string> wordBreak(string s, unordered_set<string> &dict) {
    int n = s.size();
    vector<vector<int>> dp(n);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= i; ++j) {
        if ((j == 0 || dp[j - 1].size()) && dict.count(s.substr(j, i - j + 1))) {
          dp[i].push_back(j);
        }
      }
    }

    vector<string> res;
    string sub;

    if (dp[n - 1].size()) {
      dfs(s, dp, res, sub, n - 1);
    }

    return res;
  }
};

int main() {
  string s = "catsanddog";
  unordered_set<string> dict = {"cat","cats","and","sand","dog"};
  Solution sol;

  auto res = sol.wordBreak(s, dict);
  for (auto str: res) {
    cout << str << endl;
  }

  return 0;
}
