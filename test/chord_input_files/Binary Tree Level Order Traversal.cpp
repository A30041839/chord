// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 16, 2014
// Update:     May 16, 2014
//
// Binary Tree Level Order Traversal
// Given a binary tree, return the level order traversal of its nodes' values. 
// (ie, from left to right, level by level).

#include "leetcode.h"

class Solution {
  void _levelOrder1(TreeNode* cur, vector<vector<int>>& res, int dep) {
    if (!cur) {
      return ;
    }
    if (res.size() < dep + 1) {
      res.resize(dep + 1);
    }
    res[dep].push_back(cur->val);
    _levelOrder1(cur->left, res, dep + 1);
    _levelOrder1(cur->right, res, dep + 1);
  }

  vector<vector<int> > levelOrder1(TreeNode *root) {
    vector<vector<int>> res;

    _levelOrder1(root, res, 0);

    return res;
  }

  vector<vector<int>> levelOrder2(TreeNode* root) {
    if (!root) {
      return {};
    }
    vector<vector<int>>  res;
    queue<pair<TreeNode*, int>> q;

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

    return res;
  }

public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    //return levelOrder1(root);
    return levelOrder2(root);
  }
};

int main() {
  return 0;
}
