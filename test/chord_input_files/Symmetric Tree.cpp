// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 15, 2014
// Update:     May 15, 2014
//
// Symmetric Tree
// Given a binary tree, check whether it is a mirror of itself (ie, symmetric
// around its center).
// For example, this binary tree is symmetric:
//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3
// But the following is not:
//    1
//   / \
//  2   2
//   \   \
//   3    3

#include "leetcode.h"

class Solution {
  bool isSymmetricHelper1(TreeNode* ltree, TreeNode* rtree) {
    if (ltree && !rtree || !ltree && rtree) {
      return false;
    }
    if (!ltree && !rtree) {
      return true;
    }
    if (ltree->val != rtree->val) {
      return false;
    }
    return isSymmetricHelper1(ltree->left, rtree->right)
      && isSymmetricHelper1(ltree->right, rtree->left);
  }

  bool isSymmetric1(TreeNode* root) {
    if (!root) {
      return true;
    }
    return isSymmetricHelper1(root->left, root->right);
  }

  bool isSymmetric2(TreeNode* root) {
    if (!root) {
      return true;
    }
    queue<TreeNode* > q;

    q.push(root->left);
    q.push(root->right);
    while (!q.empty()) {
      TreeNode* ltree = q.front();
      q.pop();
      TreeNode* rtree = q.front();
      q.pop();
      if (!ltree && !rtree) {
        continue;
      }
      if (ltree && !rtree || !ltree && rtree) {
        return false;
      }
      if (ltree->val != rtree->val) {
        return false;
      }
      q.push(ltree->left);
      q.push(rtree->right);

      q.push(ltree->right);
      q.push(rtree->left);
    }

    return true;
  }

public:
  bool isSymmetric(TreeNode *root) {
    // return isSymmetric1(root);
    return isSymmetric2(root);
  }
};

int main() {
  return 0;
}
