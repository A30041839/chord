// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Search in Rotated Sorted Array II
// Follow up for "Search in Rotated Sorted Array":
//
// What if duplicates are allowed?
// Would this affect the run-time complexity? How and why?
// Write a function to determine if a given target is in the array.
//
// refer
// https://oj.leetcode.com/discuss/223/when-there-are-duplicates-the-worst-case-is-could-we-do-better

#include "leetcode.h"

class Solution {
public:
  bool search(vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;

    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if (nums[mid] == target) {
        return true;
      }

      if (nums[lo] == nums[mid]) {
        while (lo <= hi && nums[lo] == nums[mid]) {
          ++lo;
        }
      } else if (nums[lo] < nums[mid]) {
        if (nums[lo] <= target && target < nums[mid]) {
          hi = mid - 1;
        } else {
          lo = mid + 1;
        }
      } else {
        if (nums[mid] < target && target <= nums[hi]) {
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }
    }

    return false;
  }
};

int main() {
  return 0;
}
