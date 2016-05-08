// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Date:       May 17, 2014
//
// Search for a Range
// Given a sorted array of integers, find the starting and ending position of a
// given target value.
//
// Your algorithm's runtime complexity must be in the order of O(log n).
//
// If the target is not found in the array, return [-1, -1].
//
// For example,
// Given [5, 7, 7, 8, 8, 10] and target value 8,
// return [3, 4].

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

class Solution {

  int _lower_bound(vector<int>& nums, int target) {
    int start = -1, end = nums.size();
    while (end - start > 1) {
      int mid = start + (end - start) / 2;
      if (nums[mid] >= target) {
        end = mid;
      } else {
        start = mid;
      }
    }
    return end;
  }

  int _upper_bound(vector<int>& nums, int target) {
    int start = -1, end = nums.size();
    while (end - start > 1) {
      int mid = start + (end - start) / 2;
      if (nums[mid] > target) {
        end = mid;
      } else {
        start = mid;
      }
    }
    return end;
  }

public:
  vector<int> searchRange(vector<int>& nums, int target) {
    if (nums.empty()) {
      return {-1, -1};
    }
    int l = _lower_bound(nums, target);
    int r = _upper_bound(nums, target);
    if (l > r - 1) {
      return {-1, -1};
    }
    return {l, r - 1};
  }
};

int main() {
  vector<int> nums = {1, 1, 1, 2};
  Solution sol;
  auto res = sol.searchRange(nums, 1);
  for (auto& ele : res) {
    cout << ele << ' ';
  }
  cout << endl;

  return 0;
}
