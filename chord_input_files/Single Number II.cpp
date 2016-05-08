// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Single Number II
// Given an array of integers, every element appears three times except for one. 
// Find that single one.
// Your algorithm should have a linear runtime complexity. Could you implement it 
// without using extra memory?

#include <iostream>

using namespace std;

class Solution {
public:
  int singleNumber(vector<int>& nums) {

    int res = 0;
    for (int i = 0; i < 32; ++i) {
      int count = 0;
      for (auto& element : nums) {

        if (element & (1 << i)) {
          ++count;
        }
      }
      if (count % 3) {
        res |= (1 << i);
      }
    }

    return res;
  }
};

int main() {
  return 0;
}
