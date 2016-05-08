// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Path Sum 2
// Given a binary tree and a sum, find all root-to-leaf paths where each path's
// sum equals the given sum.

#include "leetcode.h"

class Solution {

  void dfs(TreeNode* cur, int rem, vector<vector<int>>& res, vector<int>& path) {
    if (!cur) {
      return ;
    }

    if (!cur->left && !cur->right) {
      if (rem == cur->val) {
        res.push_back(path);
        res.back().push_back(cur->val);
        return;
      }
    }

    rem -= cur->val;
    path.push_back(cur->val);
    if (cur->left) {
      dfs(cur->left, rem, res, path);
    }
    if (cur->right) {
      dfs(cur->right, rem, res, path);
    }
    path.pop_back();
  }

  vector<vector<int>> pathSum1(TreeNode* root, int sum) {
    vector<vector<int>> res;
    vector<int> path;

    dfs(root, sum, res, path);

    return res;
  }

public:
  vector<vector<int> > pathSum(TreeNode *root, int sum) {
    // dfs version
    return pathSum1(root, sum);
  }
};

int main() {
  return 0;
}
