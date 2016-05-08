// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 18, 2014
// Update:     May 18, 2014
//
// Same Tree
// Given two binary trees, write a function to check if they are equal or not.
// Two binary trees are considered equal if they are structurally identical and
// the nodes have the same value.

#include "leetcode.h"

class Solution {
  bool isSameTree1(TreeNode* p, TreeNode* q) {
    if (!p && q || p && !q) {
      return false;
    }
    if (!p && !q) {
      return true;
    }
    if (p->val != q->val) {
      return false;
    }
    return isSameTree1(p->left, q->left) && isSameTree1(p->right, q->right);
  }

  bool isSameTree2(TreeNode* p, TreeNode* q) {
    if (!p && !q) {
      return true;
    }
    queue<TreeNode* > que;

    que.push(p);
    que.push(q);
    while (!que.empty()) {
      TreeNode* ptree = que.front();
      que.pop();
      TreeNode* qtree = que.front();
      que.pop();

      if (!ptree && !qtree) {
        continue;
      }
      if (ptree && !qtree || !ptree && qtree) {
        return false;
      }
      if (ptree->val != qtree->val) {
        return false;
      }
      que.push(ptree->left);
      que.push(qtree->left);

      que.push(ptree->right);
      que.push(qtree->right);
    }

    return true;
  }

public:
  bool isSameTree(TreeNode *p, TreeNode *q) {
    // return isSameTree1(p, q);
    return isSameTree2(p, q);
  }
};

int main() {
  return 0;
}
