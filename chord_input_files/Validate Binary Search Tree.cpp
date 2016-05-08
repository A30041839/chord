// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 16, 2014
// Update:     May 16, 2014
//
// Validate Binary Search Tree
// Given a binary tree, determine if it is a valid binary search tree (BST).
// Assume a BST is defined as follows:
// The left subtree of a node contains only nodes with keys less than the node's 
// key.
// The right subtree of a node contains only nodes with keys greater than the
// node's key.
// Both the left and right subtrees must also be binary search trees.

#include "leetcode.h"

class Solution {
  bool isValidBST1(TreeNode* cur, int low, int high) {
    if (cur == nullptr) {
      return true;
    }
    if (cur->val <= low || cur->val >= high) {
      return false;
    }
    return isValidBST1(cur->left, low, cur->val) &&
      isValidBST1(cur->right, cur->val, high);
  }

  bool isValidBST1(TreeNode* root) {
    return isValidBST1(root, INT_MIN, INT_MAX);
  }

  bool isValidBSTHelper2(TreeNode* cur, TreeNode*& prev) { // &
    if (!cur) {
      return true;
    }

    if (!isValidBSTHelper2(cur->left, prev)) {
      return false;
    }
    if (prev) {
      if (prev->val >= cur->val) {
        return false;
      }
    }
    prev = cur;
    if (!isValidBSTHelper2(cur->right, prev)) {
      return false;
    }
    return true;
  }

  // For a binary search tree, its inorder should be ascendent
  bool isValidBST2(TreeNode* root) {
    TreeNode* prev = nullptr;
    return isValidBSTHelper2(root, prev);
  }

public:
  bool isValidBST(TreeNode *root) {
    // return isValidBST1(root);
    return isValidBST2(root);
  }
};

int main() {
  return 0;
}
