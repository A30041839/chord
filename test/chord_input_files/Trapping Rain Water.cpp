// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 5, 2014
// Update:     May 5, 2014
//
// Trapping Rain Water
// Given n non-negative integers representing an elevation map where the width of 
// each bar is 1, compute how much water it is able to trap after raining.
// For example, 
// Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

#include "leetcode.h"

class Solution {
public:
  int trap(vector<int>& height) {
    int n = (int)height.size();
    if (n < 3) {
      return 0;
    }

    int lmx[n], rmx[n];
    lmx[0] = height[0];
    for (int i = 1; i < n; ++i) {
      lmx[i] = max(height[i], lmx[i - 1]);
    }

    rmx[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      rmx[i] = max(height[i], rmx[i + 1]);
    }

    int res = 0;
    for (int i = 1; i < n - 1; ++i) {
      // min(lmx[i], rmx[i]) larger than height[i] always
      res += min(lmx[i], rmx[i]) - height[i];
    }

    return res;
  }
};

int main() {
  return 0;
}
