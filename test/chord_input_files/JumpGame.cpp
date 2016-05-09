// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Jump Game
// Given an array of non-negative integers, you are initially positioned at the 
// first index of the array.
// Each element in the array represents your maximum jump length at that position.
// Determine if you are able to reach the last index.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool canJump(vector<int>& nums) {
    int maxpos = 0, i = 0;
    int n = (int)nums.size();

    while (i <= maxpos) {
      maxpos = max(maxpos, nums[i] + i);
      if (maxpos >= n - 1) {
        return true;
      }
      ++i;
    }

    return false;
  }
};

int main() {
  return 0;
}
