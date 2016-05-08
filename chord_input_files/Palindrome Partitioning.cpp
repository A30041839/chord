// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     Jul 28, 2014
//
// Palindrome Partitioning
// Given a string s, partition s such that every substring of the partition is a
// palindrome.
// Return all possible palindrome partitioning of s.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
  void get_ans(const string& s, vector<vector<int>>& pre, vector<vector<string>>& res,
    vector<string>& sub, int cur) {
    if (cur < 0) {
      res.push_back(vector<string>(sub.rbegin(), sub.rend()));
      return ;
    }
    for (auto& i : pre[cur]) {
      string str = s.substr(i + 1, cur - (i + 1) + 1);
      sub.push_back(str);
      get_ans(s, pre, res, sub, i);
      sub.pop_back();
    }
  }
public:
  vector<vector<string>> partition(string s) {
    if (s.empty()) {
      return {};
    }
    int n = s.size();
    vector<bool> is_palind(n, false);
    vector<vector<int>> pre(n, vector<int>());

    is_palind[0] = true;
    for (int i = 0; i < n; ++i) {
      is_palind[i] = true;
      pre[i].push_back(i - 1);
      for (int j = 0; j < i; ++j) {
        is_palind[j] = (s[j] == s[i]) && is_palind[j + 1];
        if (is_palind[j]) {
          pre[i].push_back(j - 1);
        }
      }
    }

    vector<vector<string>> res;
    vector<string> sub;

    get_ans(s, pre, res, sub, n - 1);

    return res;
  }
};

int main() {
  return 0;
}
