// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 14, 2014
// Update:     Jun 29, 2014
//
// Binary Tree Inorder Traversal
// Given a binary tree, return the inorder traversal of its nodes' values.

#include "leetcode.h"

class Solution {

  void inorderTraversalHelper1(TreeNode* cur, vector<int>& res) {
    if (!cur) {
      return ;
    }
    inorderTraversalHelper1(cur->left, res);
    res.push_back(cur->val);
    inorderTraversalHelper1(cur->right, res);
  }

  vector<int> inorderTraversal1(TreeNode* root) {
    vector<int> res;

    inorderTraversalHelper1(root, res);

    return res;
  }

  vector<int> inorderTraversal2(TreeNode* root) {
    if (!root) {
      return {};
    }

    vector<int> res;
    stack<TreeNode* > stk;
    TreeNode* cur = root;

    while (cur || stk.size()) {
      if (cur) {
        // push() here
        stk.push(cur);
        cur = cur->left;
      } else {
        // push_back() here
        res.push_back(stk.top()->val);
        cur = stk.top()->right;
        // pop()
        stk.pop();
      }
    }

    return res;
  }

  // Morris traversal, O(1) space, O(N) time complexity
  vector<int> inorderTraversal3(TreeNode* root) {
    if (!root) {
      return {};
    }
    TreeNode* cur = root, *pre = nullptr;
    vector<int> res;

    while (cur) {
      if (!cur->left) {
        res.push_back(cur->val);
        cur = cur->right;
      } else {
        // find the predecessor of cur node
        pre = cur->left;
        while (pre->right && pre->right != cur) {
          pre = pre->right;
        }

        if (!pre->right) {
          // Change the tree structure, connect the pre->right to its successor
          pre->right = cur;
          cur = cur->left;
        } else {
          pre->right = nullptr; // recover the tree structure
          res.push_back(cur->val);
          cur = cur->right;
        }
      }
    }

    return res;
  }

  // Using Iterator
  class InorderIterator {

    class Frame {
    public:
      int state;
      TreeNode* node;

      explicit Frame(TreeNode* node = nullptr): state(0), node(node) {
      }
    };

    stack<Frame> stk;
    TreeNode* next_node;

  public:
    explicit InorderIterator(TreeNode* root): next_node(nullptr) {
      stk.push(Frame(root));
    }

    bool has_next() {

      next_node = nullptr;
      while (!stk.empty()) {
        Frame& cur = stk.top();
        if (!cur.node) {
          stk.pop();
          continue;
        }

        if (cur.state == 0) {
          cur.state = 1;
          stk.push(Frame(cur.node->left));
        } else if (cur.state == 1) {
          cur.state = 2;
          stk.push(Frame(cur.node->right));

          next_node = cur.node;
          return true;
        } else {
          stk.pop();
        }
      }

      return false;
    }

    int next() {
      assert(next_node);
      return next_node->val;
    }
  };

  vector<int> inorderTraversal4(TreeNode *root) {
    vector<int> res;

    InorderIterator ii(root);
    while (ii.has_next()) {
      res.push_back(ii.next());
    }

    return res;
  }

public:
  vector<int> inorderTraversal(TreeNode *root) {
    //return inorderTraversal1(root);
    //return inorderTraversal2(root);
    //return inorderTraversal3(root);
    return inorderTraversal4(root);
  }
};

int main() {
  return 0;
}
