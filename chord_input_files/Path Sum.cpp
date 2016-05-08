// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Path Sum
// Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up 
// all the values along the path equals the given sum.

#include "leetcode.h"

class Solution {
  bool hasPathSum1(TreeNode* root, int sum) {
    if (!root) {
      return false;
    }
    sum -= root->val;
    // when the left child and right child are both nullptr can root be the leaf
    // node
    if (!root->left && !root->right) {
      return sum == 0;
    }
    return hasPathSum1(root->left, sum) || hasPathSum1(root->right, sum);
  }

  bool hasPathSum2(TreeNode* cur, int sum) {
    if (!cur) {
      return false;
    }

    queue<pair<TreeNode*, int>> que;
    int rem = 0;

    que.push({cur, sum});
    while (que.size()) {
      cur = que.front().first;
      rem = que.front().second;
      que.pop();

      if (!cur->left and !cur->right and rem == cur->val) {
        return true;
      }
      // Shouldn't add this judgement.
      //if (rem < cur->val) {
        //continue;
      //}
      if (cur->left) {
        que.push({cur->left, rem - cur->val});
      }
      if (cur->right) {
        que.push({cur->right, rem - cur->val});
      }
    }

    return false;
  }

public:
  bool hasPathSum(TreeNode *root, int sum) {
    // dfs version
    return hasPathSum1(root, sum);
    // bfs version
    return hasPathSum2(root, sum);
  }
};

int main() {
  return 0;
}
