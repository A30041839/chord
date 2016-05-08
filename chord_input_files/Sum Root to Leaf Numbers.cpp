// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Sum Root to Leaf Numbers
// Given a binary tree containing digits from 0-9 only, each root-to-leaf path 
// could represent a number.
// An example is the root-to-leaf path 1->2->3 which represents the number 123.
// Find the total sum of all root-to-leaf numbers.
// For example,
//   1
//  / \
// 2   3
// The root-to-leaf path 1->2 represents the number 12.
// The root-to-leaf path 1->3 represents the number 13.
// Return the sum = 12 + 13 = 25.

#include "leetcode.h"

class Solution {
  void _sumNumbers(TreeNode* cur, int& res, int sum) {
    // Cur node is a leaf node
    if (cur and !cur->left and !cur->right) {
      res += sum * 10 + cur->val;
      return ;
    }
    // Empty node, not a leaf node
    if (!cur) {
      return ;
    }

    sum = sum * 10 + cur->val;
    _sumNumbers(cur->left, res, sum);
    _sumNumbers(cur->right, res, sum);
  }

public:
  int sumNumbers(TreeNode *root) {
    if (!root) {
      return 0;
    }

    int res = 0;
    _sumNumbers(root, res, 0);
    return res;
  }
};

int main() {
  return 0;
}
