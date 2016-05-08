// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Construct Binary Tree from Inorder and Postorder Traversal
// Given inorder and postorder traversal of a tree, construct the binary tree.
//
// Note:
// You may assume that duplicates do not exist in the tree.

#include "leetcode.h"

class Solution {
  typedef vector<int>::iterator ITER;

  TreeNode* _build(ITER initr, ITER postitr, int n) {
    if (!n) {
      return nullptr;
    }

    int val = *(postitr + n - 1);
    TreeNode* root = new TreeNode(val);
    int pos = find(initr, initr + n, val) - initr;

    root->left = _build(initr, postitr, pos);
    root->right = _build(initr + pos + 1, postitr + pos, n - pos - 1);

    return root;
  }

public:
  TreeNode *buildTree(vector<int>& inorder, vector<int>& postorder) {
    return _build(inorder.begin(), postorder.begin(), inorder.size());
  }
};

int main() {
  return 0;
}
