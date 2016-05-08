// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 17, 2014
//
// Binary Tree Zigzag Level Order Traversal
// Given a binary tree, return the zigzag level order traversal of its nodes'
// values. (ie, from left to right, then right to left for the next level 
// and alternate between).

#include "leetcode.h"

class Solution {
  void zigzagLevelOrderHelper1(TreeNode* cur, vector<vector<int>>& res, int dep) {
    if (!cur) {
      return ;
    }

    if (dep + 1 > (int)res.size()) {
      res.resize(dep + 1);
    }
    res[dep].push_back(cur->val);
    zigzagLevelOrderHelper1(cur->left, res, dep + 1);
    zigzagLevelOrderHelper1(cur->right, res, dep + 1);
  }

  vector<vector<int>> zigzagLevelOrder1(TreeNode *root) {
    vector<vector<int>> res;

    zigzagLevelOrderHelper1(root, res, 0);
    for (int i = 0; i < (int)res.size(); ++i) {
      if (i & 1) {
        reverse(res[i].begin(), res[i].end());
      }
    }

    return res;
  }

  vector<vector<int>> zigzagLevelOrder2(TreeNode* root) {
    if (!root) {
      return {};
    }
    vector<vector<int>> res;
    stack<TreeNode*> stk[2];
    int which = 0, dep = 0;

    stk[which].push(root);
    while (!stk[which].empty()) {
      while (!stk[which].empty()) {
        TreeNode* cur = stk[which].top();
        stk[which].pop();

        if (dep + 1 > (int)res.size()) {
          res.resize(dep + 1);
        }
        res[dep].push_back(cur->val);

        if (which ^ 1) {
          if (cur->left) {
            stk[which ^ 1].push(cur->left);
          }
          if (cur->right) {
            stk[which ^ 1].push(cur->right);
          }
        } else {
          if (cur->right) {
            stk[which ^ 1].push(cur->right);
          }
          if (cur->left) {
            stk[which ^ 1].push(cur->left);
          }
        }
      }
      ++dep;
      which ^= 1;
    }

    return res;
  }

public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    // return zigzagLevelOrder1(root);
    return zigzagLevelOrder2(root);
  }
};

int main() {
  return 0;
}
