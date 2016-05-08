#include "leetcode.h"

class Solution {
  void _flatten1(TreeNode*& cur) {
    if (!cur) {
      return ;
    }

    TreeNode* l = cur->left, *r = cur->right;
    cur->left = nullptr;
    if (l) {
      cur->right = l;
      cur = cur->right;
      _flatten1(cur);
    }
    if (r) {
      cur->right = r;
      cur = cur->right;
      _flatten1(cur);
    }
  }

  void flatten1(TreeNode* root) {
    _flatten1(root);
  }

  void flatten2(TreeNode* root) {
    if (!root) {
      return ;
    }

    stack<TreeNode* > stk;
    stk.push(root);

    while (!stk.empty()) {
      TreeNode* cur = stk.top();
      stk.pop();

      if (cur->right) { // push right child earlier than left child
        stk.push(cur->right);
      }
      if (cur->left) {
        stk.push(cur->left);
        cur->left = nullptr;
      }

      if (root != cur) {
        root->right = cur;
        root = root->right;
      }
    }
  }

public:
  void flatten(TreeNode *root) {
    // flatten1(root);
    flatten2(root);
  }
};

int main() {
  return 0;
}
