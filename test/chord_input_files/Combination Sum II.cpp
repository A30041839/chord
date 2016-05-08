// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 14, 2014
// Update:     May 14, 2014
//
// Combination Sum II
// Given a collection of candidate numbers (C) and a target number (T),
// find all unique combinations in C where the candidate numbers sums to T.
// Each number in C may only be used once in the combination.
//
// Note:
// All numbers (including target) will be positive integers.
// Elements in a combination (a1, a2, .. , ak) must be in non-descending order.
// (ie, a1 <= a2 <= ... <= ak).
// The solution set must not contain duplicate combinations.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  void dfs(const vector<int>& num, int remain, vector<vector<int>>& res, 
    vector<int>& sub, int start) {
    if (remain == 0) {
      res.push_back(sub);
      return ;
    }

    for (int i = start; i < (int)num.size(); ++i) {
      if (num[i] > remain) {
        break;
      }
      if (i > start && num[i] == num[i - 1]) {
        continue;
      }
      // there is another way to prune
      // TODO
      sub.push_back(num[i]);
      dfs(num, remain - num[i], res, sub, i + 1); // !! i + 1
      sub.pop_back();
    }
  }
public:
  vector<vector<int> > combinationSum2(vector<int> &num, int target) {
    vector<vector<int>> res;
    vector<int> sub;

    sort(num.begin(), num.end());
    dfs(num, target, res, sub, 0);

    return res;
  }
};

int main() {
  return 0;
}
