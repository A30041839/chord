// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 17, 2014
// Update:     Jun 29, 2014
//
// Binary Tree Postorder Traversal 
// Given a binary tree, return the postorder traversal of its nodes' values.

#include "leetcode.h"

class Solution {

  // Recursive solution
  void postorderTraversalHelper1(TreeNode* cur, vector<int>& res) {
    if (!cur) {
      return ;
    }
    postorderTraversalHelper1(cur->left, res);
    postorderTraversalHelper1(cur->right, res);
    res.push_back(cur->val);
  }

  vector<int> postorderTraversal1(TreeNode* root) {
    vector<int> res;

    postorderTraversalHelper1(root, res);

    return res;
  }

  // Iterative solution
  vector<int> postorderTraversal2(TreeNode* root) {
    vector<int> res;
    stack<TreeNode* > stk;
    TreeNode* cur = root, *last = nullptr;

    while (cur || stk.size()) {
      if (cur) {
        stk.push(cur);
        cur = cur->left;
      } else {
        TreeNode* subroot = stk.top();
        // If subroot->right equals to last, means subroot->right hsa been
        // visited before. Adding this condition is to avoid visiting many times.
        if (subroot->right && subroot->right != last) {
          cur = subroot->right;
        } else {
          res.push_back(stk.top()->val);
          last = stk.top();
          stk.pop();
        }
      }
    }

    return res;
  }

  void _push(vector<int>& res, TreeNode* start, TreeNode* end) {
    int n = res.size();
    TreeNode* cur = start;
    while (cur != end) {
      res.push_back(cur->val);
      cur = cur->right;
    }
    res.push_back(cur->val);

    reverse(res.begin() + n, res.end());
  }

  // Mirros traversal, O(1) space, O(N) time complexity
  vector<int> postorderTraversal3(TreeNode* root) {
    if (!root) {
      return {};
    }
    TreeNode dummy(0), *cur = &dummy, *pre = nullptr;
    cur->left = root;
    vector<int> res;

    while (cur) {
      if (!cur->left) {
        cur = cur->right;
      } else {
        pre = cur->left;
        while (pre->right && pre->right != cur) {
          pre = pre->right;
        }

        if (!pre->right) {
          pre->right = cur;
          cur = cur->left;
        } else {
          _push(res, cur->left, pre);
          pre->right = nullptr;
          cur = cur->right;
        }
      }
    }

    return res;
  }

  // Using iterator
  class PostorderIterator {

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
    explicit PostorderIterator(TreeNode* node = nullptr): next_node(nullptr) {
      stk.push(Frame(node));
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
        } else {
          next_node = cur.node;
          stk.pop();
          return true;
        }
      }
      return false;
    }

    int next() {
      assert(next_node);
      return next_node->val;
    }
  };

  vector<int> postorderTraversal4(TreeNode *root) {
    vector<int> res;

    PostorderIterator pi(root);
    while (pi.has_next()) {
      res.push_back(pi.next());
    }

    return res;
  }

public:
  vector<int> postorderTraversal(TreeNode *root) {
    //return postorderTraversal1(root);
    //return postorderTraversal2(root);
    //return postorderTraversal3(root);
    return postorderTraversal4(root);
  }
};

int main() {
  return 0;
}
