// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Unique Binary Search Trees II 
// Given n, generate all structurally unique BST's (binary search trees) that 
// store values 1...n.
// 
// For example,
// Given n = 3, your program should return all 5 unique BST's shown below.
// 
//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

#include "leetcode.h"

class Solution {
  void _generate(int start, int end, vector<TreeNode* >& res) {
    if (start > end) {
      res = {nullptr};
      return ;
    }

    for (int mid = start; mid <= end; ++mid) {

      vector<TreeNode* > left, right;
      _generate(start, mid - 1, left);
      _generate(mid + 1, end, right);

      for (auto& ltree : left) {
        for (auto& rtree : right) {
          TreeNode* root = new TreeNode(mid);
          root->left = ltree;
          root->right = rtree;
          res.push_back(root);
        }
      }
    }
  }

public:
  vector<TreeNode *> generateTrees(int n) {
    vector<TreeNode* > res = {};

    _generate(1, n, res);

    return res;
  }
};

int main() {
  Solution sol;
  vector<TreeNode* > res = sol.generateTrees(1);

  cout << res.size() << endl;
  for (auto& tree : res) {
    level_order(tree);
  }

  return 0;
}
