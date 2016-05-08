// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 5, 2014
// Update:     May 5, 2014
//
// Container With Most Water
// Given n non-negative integers a1, a2, ..., an, where each represents a point
// at coordinate (i, ai).
// n vertical lines are drawn such that the two endpoints of line i is at
// (i, ai) and (i, 0).
// Find two lines, which together with x-axis forms a container, such that the
// container contains the most water.
//
// Note:
// You may not slant the container.

#include "leetcode.h"

class Solution {
  int maxArea1(vector<int> &height) {
    int n = height.size();
    int l = 0, r = n - 1, res = 0;

    while (l < r) {
      int minh = min(height[l], height[r]);
      res = max(res, minh * (r - l));
      if (height[l] < height[r]) {
        while (l < r && height[l] <= minh) {
          ++l;
        }
      } else {
        while (l < r && height[r] <= minh) {
          --r;
        }
     }
    }

    return res;
  }

public:
  int maxArea(vector<int> &height) {
    return maxArea1(height);
  }
};

int main() {
  return 0;
}
