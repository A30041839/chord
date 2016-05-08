// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 5, 2014
// Update:     May 5, 2014
//
// Sort Colors
// Given an array with n objects colored red, white or blue, sort them so that 
// objects of the same color
// are adjacent, with the colors in the order red, white and blue.
// Here, we will use the integers 0, 1, and 2 to represent the color red, white,
// and blue respectively.
//
// Note:
// You are not suppose to use the library's sort function for this problem.
// Follow up:
// A rather straight forward solution is a two-pass algorithm using counting sort.
// First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with 
// total number of 0's, then 1's and followed by 2's.
// Could you come up with an one-pass algorithm using only constant space?

#include "leetcode.h"

class Solution {
  void swap(int& a, int& b) {
    if (a == b) {
      return ;
    }
    a ^= b ^= a ^= b;
  }

public:
  void sortColors(vector<int>& nums) {
    int n = (int)nums.size();
    if (n < 2) {
      return ;
    }
    int c0 = 0, c2 = n - 1, i = 0;

    while (i <= c2) {
      if (nums[i] == 0) {
        swap(nums[i++], nums[c0++]);
      } else if (nums[i] == 2) {
        swap(nums[i], nums[c2--]);
      } else {
        ++i;
      }
    }
  }
};

int main() {
  vector<int> a = {1, 0};

  Solution sol;
  sol.sortColors(a);
  for (auto& ele : a) {
    cout << ele << ' ';
  }
  cout << endl;

  return 0;
}
