// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Search in Rotated Sorted Array
// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//
// You are given a target value to search. If found in the array return its
// index, otherwise return -1.
// You may assume no duplicate exists in the array.
//
// refer
// http://leetcode.com/2010/04/searching-element-in-rotated-array.html

#include "leetcode.h"

class Solution {
public:
  int search(vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;

    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if (nums[mid] == target) {
        return mid;
      }

      if (nums[lo] <= nums[mid]) { // !! <=
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

    return -1;
  }
};

int main() {
  vector<int> nums = {3, 1};
  Solution sol;
  int res = sol.search(nums, 1);
  cout << res << endl;

  return 0;
}
