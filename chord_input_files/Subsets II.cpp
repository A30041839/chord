// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 7, 2014
// Update:     Jul 13, 2014
//
// Subsets II
// Given a collection of integers that might contain duplicates, S, return all
// possible subsets.
//
// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.
// For example,
// If S = [1,2,2], a solution is:
// [
//  [2],
//  [1],
//  [1,2,2],
//  [2,2],
//  [1,2],
//  []
// ]
/
#include "leetcode.h"

class Solution {

  // Bit Manipulation
  vector<vector<int>> subsetsWithDup1(vector<int>& S) {
    int n = S.size();
    vector<vector<int>> res;

    sort(S.begin(), S.end());
    for (int i = 0; i < (1 << n); ++i) {
      vector<int> sub;
      for (int j = 0; j < n; ++j) {
        if ((1 << j) & i) {
          sub.push_back(S[j]);
        }
      }

      if (find(res.begin(), res.end(), sub) == res.end()) {
        res.push_back(sub);
      }
    }

    return res;
  }

  void dfs(const vector<int>& S, vector<vector<int>>& res, vector<int>& sub, int start) {
    res.push_back(sub);

    for (int i = start; i < S.size(); ++i) {
      if (i > start && S[i] == S[i - 1]) {
        continue;
      }
      sub.push_back(S[i]);
      dfs(S, res, sub, i + 1);
      sub.pop_back();
    }
  }

  // DFS
  vector<vector<int>> subsetsWithDup2(vector<int>& S) {
    vector<vector<int>> res;
    vector<int> sub;

    sort(S.begin(), S.end());
    dfs(S, res, sub, 0);

    return res;
  }

  // pure recursion
  vector<vector<int>> subsetsWithDup3(vector<int>& S) {
    if (S.empty()) {
      return {{}};
    }

    vector<vector<int>> res = {{}};
    sort(S.begin(), S.end());
    int n = S.size();
    for (int i = 0; i < n; ++i) {
      if (i > 0 && S[i] == S[i - 1]) {
        continue;
      }
      vector<int> subvec(S.begin() + i + 1, S.end());
      auto subs = subsetsWithDup(subvec);
      for (auto& sub : subs) {
        vector<int> cur = {S[i]};
        for (auto& ele : sub) {
          cur.push_back(ele);
        }
        res.push_back(cur);
      }
    }

    return res;
  }

public:
  vector<vector<int> > subsetsWithDup(vector<int> &S) {
    //return subsetsWithDup1(S);
    //return subsetsWithDup2(S);
    return subsetsWithDup3(S);
  }
};

int main() {
  vector<int> v = {1, 2, 2};
  Solution sol;
  vector<vector<int>> res = sol.subsetsWithDup(v);
  print_vector2(res);

  return 0;
}
