// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Search Insert Position
//
// Given a sorted array and a target value, return the index if the target is
// found. If not, return the index where it would be if it were inserted in
// order.
//
// You may assume no duplicates in the array.
// Here are few examples.
// [1,3,5,6], 5 → 2
// [1,3,5,6], 2 → 1
// [1,3,5,6], 7 → 4
// [1,3,5,6], 0 → 0

#include "leetcode.h"

class Solution {
  int _lower_bound1(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;

    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      if (target <= nums[mid]) {
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }
    return hi + 1;
  }
  int lower_bound1(vector<int>& nums, int target) {
    int p = _lower_bound1(nums, target);
    return p == (int)nums.size() ? nums.size() : p;
  }

  // Invariant relation.
  int lower_bound2(vector<int>& nums, int target) {
    // invariatn relation is A[start] < target <= A[end]
    int start = -1, end = nums.size();

    while (end - start > 1) {
      int mid = start + (end - start) / 2;
      if (nums[mid] >= target) { // design to fit the invariatn relation
        end = mid;
      } else {
        start = mid;
      }
    }

    return end;
  }

public:
  int searchInsert(vector<int>& nums, int target) {
    //return lower_bound1(nums, target);
    return lower_bound2(nums, target);
  }
};

int main() {
  Solution sol;
  vector<int> nums = {0, 1, 3, 3, 3, 8, 9, 12};
  int pos = sol.searchInsert(nums, 4);
  cout << pos << endl;
  return 0;
}
