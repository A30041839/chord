// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 15, 2014
// Update:     May 15, 2014
//
// Convert Sorted List to Binary Search Tree
// Given a singly linked list where elements are sorted in ascending order,
// convert it to a height balanced BST.

#include "leetcode.h"

class Solution {
  TreeNode* _convert(ListNode*& cur, int st, int ed) {
    if (st > ed) {
      return nullptr;
    }

    int mid = st + (ed - st) / 2;
    TreeNode* root = new TreeNode(0);
    root->left = _convert(cur, st, mid - 1);
    root->val = cur->val;
    cur = cur->next;
    root->right = _convert(cur, mid + 1, ed);

    return root;
  }


public:
  TreeNode *sortedListToBST(ListNode *head) {
    int len = 0;
    ListNode* cur = head;

    while (cur) {
      cur = cur->next;
      ++len;
    }

    return _convert(head, 0, len - 1);
  }
};

int main(){
  return 0;
}
