// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 17, 2014
//
// Binary Tree Level Order Traversal II
// Given a binary tree, return the bottom-up level order traversal of its nodes'
// values. 
// (ie, from left to right, level by level from leaf to root).

#include "leetcode.h"

class Solution {
  void _levelOrderBottom1(TreeNode* cur, vector<vector<int>>& res, int dep) {
    if (!cur) {
      return ;
    }
    if (dep + 1 > res.size()) {
      res.resize(dep + 1);
    }

    res[dep].push_back(cur->val);
    _levelOrderBottom1(cur->left, res, dep + 1);
    _levelOrderBottom1(cur->right, res, dep + 1);
  }

  vector<vector<int> > levelOrderBottom1(TreeNode *root) {
    vector<vector<int>> res;

    _levelOrderBottom1(root, res, 0);
    reverse(res.begin(), res.end());

    return res;
  }

  vector<vector<int>> levelOrderBottom2(TreeNode* root) {
    if (!root) {
      return {};
    }
    queue<pair<TreeNode*, int>> q;
    vector<vector<int>> res;

    q.push({root, 0});
    while (!q.empty()) {
      TreeNode* cur = q.front().first;
      int dep = q.front().second;
      q.pop();

      if (dep + 1 > res.size()) {
        res.resize(dep + 1);
      }
      res[dep].push_back(cur->val);
      if (cur->left) {
        q.push({cur->left, dep + 1});
      }
      if (cur->right) {
        q.push({cur->right, dep + 1});
      }
    }
    reverse(res.begin(), res.end());

    return res;
  }

public:
  vector<vector<int>> levelOrderBottom(TreeNode *root) {
    // return levelOrderBottom1(root);
    return levelOrderBottom2(root);
  }
};

int main() {
  return 0;
}
