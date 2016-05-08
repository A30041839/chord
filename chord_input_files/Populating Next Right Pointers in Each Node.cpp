// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 20, 2014
// Update:     May 20, 2014
//
// Populating Next Right Pointers in Each Node
// Populate each next pointer to point to its next right node. If there is no
// next right node, the next pointer should be set to nullptr.
// Initially, all next pointers are set to nullptr.
//
// Note:
// You may only use constant extra space.
// You may assume that it is a perfect binary tree (ie, all leaves are at the 
// same level, and every parent has two children).

#include "leetcode.h"

class Solution {
  void connect1(TreeLinkNode* cur) {
    if (!cur) {
      return ;
    }
    if (!cur->left && !cur->right) {
      return ;
    }
    cur->left->next = cur->right;
    if (cur->next) {
      cur->right->next = cur->next->left;
    }
    connect1(cur->left);
    connect1(cur->right);
  }

  void connect2(TreeLinkNode* root) {
    if (!root) {
      return ;
    }

    TreeLinkNode* p = root;
    while (p && p->left) {
      TreeLinkNode* q = p;
      while (q && q->left) {
        q->left->next = q->right;
        if (q->next) {
          q->right->next = q->next->left;
        }
        q = q->next;
      }
      p = p->left;
    }
  }

public:
  void connect(TreeLinkNode *root) {
    //connect1(root);
    connect2(root);
  }
};

int main() {
  return 0;
}
