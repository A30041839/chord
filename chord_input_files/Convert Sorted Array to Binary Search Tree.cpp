// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 15, 2014
// Update:     May 15, 2014
//
// Convert Sorted Array to Binary Search Tree
// Given an array where elements are sorted in ascending order, convert it to 
// a height balanced BST.

#include "leetcode.h"

class Solution {
  TreeNode* _sortedArrayToBST(vector<int>& num, int start, int end) {
    if (end < start) {
      return nullptr;
    }

    int mid = start + (end - start) / 2;
    TreeNode* subroot = new TreeNode(num[mid]);
    subroot->left = _sortedArrayToBST(num, start, mid - 1);
    subroot->right = _sortedArrayToBST(num, mid + 1, end);

    return subroot;
  }

public:
  TreeNode *sortedArrayToBST(vector<int> &num) {
    if (num.empty()) {
      return nullptr;
    }
    return _sortedArrayToBST(num, 0, num.size() - 1);
  }
};

int main() {
  return 0;
}

