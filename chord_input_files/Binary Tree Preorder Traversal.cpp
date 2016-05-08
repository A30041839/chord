// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 14, 2014
// Update:     Jun 29, 2014
//
// Binary Tree Preorder Traversal
// Given a binary tree, return the preorder traversal of its nodes' values.

#include "leetcode.h"

using namespace std;

class Solution {
  void preorderTraversalHelper1(TreeNode* cur, vector<int>& res) {
    if (!cur) {
      return ;
    }
    res.push_back(cur->val);
    preorderTraversalHelper1(cur->left, res);
    preorderTraversalHelper1(cur->right, res);
  }

  // Recursive solution
  vector<int> preorderTraversal1(TreeNode* root) {
    vector<int> res;

    preorderTraversalHelper1(root, res);

    return res;
  }

  // Iterative solution
  vector<int> preorderTraversal2(TreeNode* root) {
    if (!root) { // !!
      return {};
    }
    vector<int> res;
    stack<TreeNode* > stk;

    stk.push(root);
    while (!stk.empty()) {
      TreeNode* cur = stk.top();
      stk.pop();
      // It should be clear when to push_back the value to the res vector
      res.push_back(cur->val);
      // The right child enter the stack first, because we want to pop left
      // child before right child
      if (cur->right) {
        stk.push(cur->right);
      }
      if (cur->left) {
        stk.push(cur->left);
      }
    }

    return res;
  }

  // Morris traversal, O(1) space, O(N) time complexity
  vector<int> preorderTraversal3(TreeNode* root) {
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
          res.push_back(cur->val);
          pre->right = cur;
          cur = cur->left;
        } else {
          pre->right = nullptr;
          cur = cur->right;
        }
      }
    }

    return res;
  }


  // Using PreorderIterator
  class PreorderIterator {

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
    explicit PreorderIterator(TreeNode* root = nullptr): next_node(nullptr) {
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
          next_node = cur.node;
          stk.push(Frame(cur.node->left));
          return true;
        } else if (cur.state == 1) {
          cur.state = 2;
          stk.push(Frame(cur.node->right));
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

  vector<int> preorderTraversal4(TreeNode *root) {
    vector<int> res;

    PreorderIterator pi(root);
    while (pi.has_next()) {
      res.push_back(pi.next());
    }

    return res;
  }

public:
  vector<int> preorderTraversal(TreeNode *root) {
    // return preorderTraversal1(root);
    //return preorderTraversal2(root);
    //return preorderTraversal3(root);
    return preorderTraversal4(root);
  }
};

int main() {
  Solution sol;
  TreeNode* root = new TreeNode(1);

  vector<int> res = sol.preorderTraversal(root);
  for (auto& element : res) {
    cout << element << endl;
  }

  return 0;
}
