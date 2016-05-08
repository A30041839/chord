// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Jump Game II
// Given an array of non-negative integers, you are initially positioned at the
// first index of the array.
// Each element in the array represents your maximum jump length at that position.
// Your goal is to reach the last index in the minimum number of jumps.

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
  int jump(vector<int>& nums) {
    int start = 0, end = 0, maxpos = 0;
    int res = 0;
    int n = (int)nums.size();

    while (end < n - 1) { // n - 1
      for (int i = start; i <= end; ++i) {
        maxpos = max(maxpos, nums[i] + i);
      }
      start = end + 1;
      end = maxpos;
      ++res;
    }

    return res;
  }
};

int main() {
  return 0;
}
