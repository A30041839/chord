// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Date:       May 10, 2014
//
// Maximum Depth of Binary Tree
// Given a binary tree, find its maximum depth.
// The maximum depth is the number of nodes along the longest path from the 
// root node down to the farthest leaf node.

#include "leetcode.h"

class Solution {

  // dfs version
  int maxDepth1(TreeNode* cur) {
    if (!cur) {
      return 0;
    }
    return max(maxDepth1(cur->left), maxDepth1(cur->right)) + 1;
  }

  // bfs version
  int maxDepth2(TreeNode* cur) {
    if (!cur) {
      return 0;
    }
    queue<pair<TreeNode*, int>> q;
    int res = 0;
    q.push({cur, 0});

    while (!q.empty()) {
      cur = q.front().first;
      int dep = q.front().second + 1;
      q.pop();

      res = max(res, dep);
      if (cur->left) {
        q.push({cur->left, dep});
      }
      if (cur->right) {
        q.push({cur->right, dep});
      }
    }
    return res;
  }

public:
  int maxDepth(TreeNode *root) {
    // return maxDepth1(root);
    return maxDepth2(root);
  }
};

int main() {
  return 0;
}
