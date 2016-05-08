// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 12, 2014
// Update:     May 12, 2014
//
// Unique Binary Search Trees
// Given n, how many structurally unique BST's (binary search trees) that store 
// values 1...n?
// For example,
// Given n = 3, there are a total of 5 unique BST's.
// 1         3     3      2      1
//  \       /     /      / \      \
//   3     2     1      1   3      2
//  /     /       \                 \
// 2     1         2                 3

#include "leetcode.h"


class Solution {
  // DP
  int numTrees1(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      // For the subtree with i node, suppose that there are j left children
      // and i - j - 1 right children
      for (int j = 0; j <= i - 1; ++j) {
        dp[i] += dp[j] * dp[i - j - 1];
      }
    }

    return dp[n];
  }
public:
  int numTrees(int n) {
    // DP
    return numTrees1(n);
    // Math
  }
};

int main() {
  return 0;
}
