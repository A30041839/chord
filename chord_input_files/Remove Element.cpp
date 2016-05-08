// Author:     ct.Liu, lcndn3@gmail.com
// Date:       Apr 30, 2014
// Update:     Apr 30, 2014
//
// Remove Element
// Given an array and a value, remove all instances of that value in place and 
// return the new length.
// The order of elements can be changed. It doesn't matter what you leave beyond
// the new length.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int removeElement1(vector<int>& nums, int val) {
    int m = 0;
    for (int i = 0; i < (int)nums.size(); ++i) {
      if (nums[i] != val) {
        nums[m++] = nums[i];
      }
    }
    return m;
  }

public:
  int removeElement(vector<int>& nums, int val) {
    return removeElement1(nums, val);
  }
};

int main() {
  return 0;
}
