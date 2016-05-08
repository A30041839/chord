// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 17, 2014
//
// Balanced Binary Tree
// Given a binary tree, determine if it is height-balanced.
// For this problem, a height-balanced binary tree is defined as a binary tree 
// in which the depth of the two subtrees of every node never differ by
// more than 1.

#include "leetcode.h"

class Solution {
  bool isBalancedHelper(TreeNode* cur, int& height) {
    if (!cur) {
      return true;
    }

    int lheight = 0, rheight = 0;
    if (!isBalancedHelper(cur->left, lheight)) {
      return false;
    }
    if (!isBalancedHelper(cur->right, rheight)) {
      return false;
    }
    height = max(lheight, rheight) + 1;

    return abs(lheight - rheight) <= 1;
  }

public:
  bool isBalanced(TreeNode *root) {
    if (root == nullptr) {
      return true;
    }

    int height = 0;
    return isBalancedHelper(root, height);
  }
};

int main() {
  return 0;
}
