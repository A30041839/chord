// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 6, 2014
// Update:     May 6, 2014
//
// Combination Sum
// Given a set of candidate numbers (C) and a target number (T), find all unique 
// combinations in C where the candidate numbers sums to T.
// The same repeated number may be chosen from C unlimited number of times.
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
  void dfs(const vector<int>& candidates, int remain, vector<vector<int>>& res, 
    vector<int>& sub, int start) {
    if (remain == 0) {
      res.push_back(sub);
      return ;
    }

    for (int i = start; i < (int)candidates.size(); ++i) {
      if (candidates[i] > remain) {
        break;
      }
      sub.push_back(candidates[i]);
      dfs(candidates, remain - candidates[i], res, sub, i);
      sub.pop_back();
    }
  }

public:
  vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> res;
    vector<int> sub;

    sort(candidates.begin(), candidates.end());
    dfs(candidates, target, res, sub, 0);

    return res;
  }
};

int main() {
  return 0;
}
