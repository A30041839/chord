// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Binary Tree Maximum Path Sum
// Given a binary tree, find the maximum path sum. The path may start and end at
// any node in the tree.

#include "leetcode.h"

class Solution {

  // Return the max path of the subtree, the path is a chain, and include the
  // TreeNode cur.
  int _maxPath1(TreeNode* cur, int& res) {
    if (!cur) {
      return 0;
    }
    int lmax = _maxPath1(cur->left, res);
    int rmax = _maxPath1(cur->right, res);
    int val = cur->val;

    int sum = 0;
    sum += lmax > 0 ? lmax : 0;
    sum += rmax > 0 ? rmax : 0;
    res = max(res, val + sum);

    // Since the end point of the result can be any node of the tree
    // val can also be returned
    return max(val, val + max(lmax, rmax));
  }

  int maxPathSum1(TreeNode *root) {
    if (!root) {
      return 0;
    }
    int res = root->val;
    _maxPath1(root, res);
    return res;
  }

public:
  int maxPathSum(TreeNode *root) {
    return maxPathSum1(root);
  }
};

int main() {
  return 0;
}
