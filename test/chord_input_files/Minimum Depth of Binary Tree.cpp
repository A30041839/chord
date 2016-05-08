// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Minimum Depth of Binary Tree
// Given a binary tree, find its minimum depth.
// The minimum depth is the number of nodes along the shortest path from the root
// node down to the nearest leaf node.

#include "leetcode.h"

class Solution {
  // dfs version
  void _minDepth1(TreeNode* cur, int dep, int& res) {
    if (cur and !cur->left and !cur->right) {
      res = min(res, dep);
      return ;
    }
    if (cur->left) {
      _minDepth1(cur->left, dep + 1, res);
    }
    if (cur->right) {
      _minDepth1(cur->right, dep + 1, res);
    }
  }

  int minDepth1(TreeNode* root) {
    if (!root) {
      return 0;
    }
    int res = INT_MAX;
    _minDepth1(root, 1, res);
    return res;
  }

  // bfs version
  int minDepth2(TreeNode* root) {
    if (!root) {
      return 0;
    }
    queue<pair<TreeNode*, int>> que;

    que.push({root, 0});
    while (!que.empty()) {
      TreeNode* cur = que.front().first;
      int dep = que.front().second + 1;
      que.pop();

      if (!cur->left and !cur->right) {
        return dep;
      }
      if (cur->left) {
        que.push({cur->left, dep});
      }
      if (cur->right) {
        que.push({cur->right, dep});
      }
    }

    return 0;
  }

public:
  int minDepth(TreeNode *root) {
    return minDepth1(root);
    //return minDepth2(root);
  }
};

int main() {
  return 0;
}
