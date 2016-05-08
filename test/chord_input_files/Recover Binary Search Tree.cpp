// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 16, 2014
// Update:     May 16, 2014
//
// Recover Binary Search Tree
// Two elements of a binary search tree (BST) are swapped by mistake.
// Recover the tree without changing its structure.

#include "leetcode.h"

// TODO
// Threaded Binary Tree: O(n) time, O(1) space

class Solution {
  void dfs(TreeNode* cur, TreeNode*& fst, TreeNode*& snd, TreeNode*& prev) {
    if (!cur) {
      return ;
    }
    dfs(cur->left, fst, snd, prev);

    if (prev) {
      if (prev->val >= cur->val) {
        if (!fst) {
          fst = prev;
        }
        snd = cur;
      }
    }
    prev = cur;

    dfs(cur->right, fst, snd, prev);
  }

public:
  void recoverTree(TreeNode *root) {
    if (!root) {
      return ;
    }
    TreeNode* fst = nullptr, *snd = nullptr, *prev = nullptr;
    dfs(root, fst, snd, prev);
    if (fst && snd) {
      swap(fst->val, snd->val);
    }
  }
};

int main() {
  return 0;
}
