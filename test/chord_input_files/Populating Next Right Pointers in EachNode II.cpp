// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 20, 2014
// Update:     May 20, 2014
//
// Populating Next Right Pointers in Each Node II 
// Follow up for problem "Populating Next Right Pointers in Each Node".
// What if the given tree could be any binary tree? Would your previous solution
// still work?
//
// Note:
// You may only use constant extra space.

#include "leetcode.h"

// Good Problem.

class Solution {
  void connect1(TreeLinkNode* cur) {
    if (!cur) {
      return ;
    }
    if (!cur->left && !cur->right) {
      return ;
    }

    TreeLinkNode* p = cur->next;
    while (p) {
      // check `left` first
      if (p->left || p->right) {
        p = p->left ? p->left : p->right;
        break;
      }
      p = p->next;
    }

    // `right` first
    if (cur->right) {
      cur->right->next = p;
    }
    if (cur->left) {
      cur->left->next = cur->right ? cur->right : p;
    }

    // `right` first
    connect1(cur->right);
    connect1(cur->left);
  }

  // O(1) space
  void connect2(TreeLinkNode* root) {
    if (!root) {
      return ;
    }

    TreeLinkNode* cur = root;
    while (cur) {
      // prev: the previous point in the same level
      // next: the first point of next level
      TreeLinkNode *prev = nullptr, *next = nullptr;
      while (cur) {
        TreeLinkNode* l = cur->left, *r = cur->right;
        if (l) {
          if (prev) {
            prev->next = l;
          }
          prev = l;
        }
        if (r) {
          if (prev) {
            prev->next = r;
          }
          prev = r;
        }
        if ((l || r) && !next) {
          next = l ? l : r;
        }
        cur = cur->next;
      }
      cur = next;
    }
  }

  void connect3(TreeLinkNode* root) {
    if (root == nullptr) {
      return ;
    }
    queue<TreeLinkNode* > q;
    TreeLinkNode* last = nullptr; // record the node visited before current node

    q.push(root);
    q.push(nullptr);

    // If there is only one node `nullptr` in the queue, quit
    while (q.size() > 1 || q.size() == 1 && q.front()) {
      TreeLinkNode* cur = q.front();
      q.pop();

      if (cur == nullptr) {
        if (last) { // when it comes to the end of each level
          last->next = nullptr;
        }
        q.push(nullptr);
        last = nullptr;
      } else {
        if (last) {
          last->next = cur;
        }
        last = cur;
        if (cur->left) {
          q.push(cur->left);
        }
        if (cur->right) {
          q.push(cur->right);
        }
      }
    }
  }

public:
  void connect(TreeLinkNode *root) {
    //  connect1(root);
    //  connect2(root);
    connect3(root);
  }
};

int main() {
  return 0;
}
