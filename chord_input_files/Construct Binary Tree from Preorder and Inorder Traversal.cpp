// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Construct Binary Tree from Preorder and Inorder Traversal 
// Given preorder and inorder traversal of a tree, construct the binary tree.
// 
// Note:
// You may assume that duplicates do not exist in the tree.
#include "leetcode.h"

class Solution {
  typedef vector<int>::iterator ITER;

  TreeNode* _build(ITER preitr, ITER initr, int n) {
    if (!n) {
      return nullptr;
    }

    int val = *preitr;
    TreeNode* root = new TreeNode(val);
    int pos = find(initr, initr + n, val) - initr;

    root->left = _build(preitr + 1, initr, pos);
    root->right = _build(preitr + pos + 1, initr + pos + 1, n - pos - 1);

    return root;
  }

public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    return _build(preorder.begin(), inorder.begin(), preorder.size());
  }
};

int main() {
  return 0;
}
