// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 18, 2014
// Update:     May 18, 2014
//
// First Missing Positive
// Given an unsorted integer array, find the first missing positive integer.
// For example,
// Given [1,2,0] return 3,
// and [3,4,-1,1] return 2.
// Your algorithm should run in O(n) time and uses constant space.

#include <iostream>

using namespace std;

class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    int n = (int)nums.size();
    for (int i = 0; i < n; ) {
      if (nums[i] <= 0 || nums[i] >= n) {
        ++i;
        continue;
      }
      if (nums[i] != i + 1 && nums[i] != nums[nums[i] - 1]) {
        swap(nums[i], nums[nums[i] - 1]);
      } else {
        ++i;
      }
    }

    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }
    return n + 1;
  }
};

int main() {
  return 0;
}
