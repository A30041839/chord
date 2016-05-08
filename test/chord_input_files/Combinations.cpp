// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 6, 2014
// Update:     May 6, 2014
//
// Combinations
// Given two integers n and k, return all possible combinations of k numbers
// out of 1 ... n.

#include "leetcode.h"

class Solution {
  void dfs(int cur, int n, int k, vector<vector<int>>& res, vector<int>& sub) {
    if (k == 0) {
      res.push_back(sub);
      return ;
    }

    for (int i = cur; i <= n; ++i) {
      if (n - cur + 1 < k) {
        break;
      }
      sub.push_back(i);
      dfs(i + 1, n, k - 1, res, sub);
      sub.pop_back();
    }
  }
public:
  vector<vector<int> > combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> sub(k, 0);

    dfs(1, n, k, res, sub);

    return res;
  }
};

int main() {
  return 0;
}
