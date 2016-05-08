// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 7, 2014
// Update:     Jul 13, 2014
//
// Subsets
// Given a set of distinct integers, S, return all possible subsets.
//
// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.
// For example,
// If S = [1,2,3], a solution is:
// [
//  [3],
//  [1],
//  [2],
//  [1,2,3],
//  [1,3],
//  [2,3],
//  [1,2],
//  []
// ]

#include "leetcode.h"

class Solution {
  void dfs(const vector<int>& nums, vector<vector<int>>& res, vector<int>& sub, int start) {
    res.push_back(sub);

    for (int i = start; i < (int)nums.size(); ++i) {
      sub.push_back(nums[i]);
      dfs(nums, res, sub, i + 1);
      sub.pop_back();
    }
  }

  vector<vector<int>> subsets1(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> sub;

    sort(nums.begin(), nums.end());
    dfs(nums, res, sub, 0);

    return res;
  }

  // pure recursion
  vector<vector<int> > subsets2(vector<int> &nums) {
    if (nums.empty()) {
      return {{}};
    }
    vector<vector<int>> res = {{}};

    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; ++i) {
      vector<int> subvec(nums.begin() + i + 1, nums.end());
      auto subs = subsets(subvec);
      for (auto& sub : subs) {
        vector<int> cur = {nums[i]};
        for (auto& ele : sub) {
          cur.push_back(ele);
        }
        res.push_back(cur);
      }
    }

    return res;
  }

public:
  vector<vector<int> > subsets(vector<int> &nums) {
    //return subsets1(nums);
    return subsets2(nums);
  }
};

int main() {
  vector<int> v = {1, 2, 3};
  Solution sol;
  vector<vector<int>> res = sol.subsets(v);
  print_vector2(res);

  return 0;
}
