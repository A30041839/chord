// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 9, 2014
// Updat:      May 9, 2014
//
// Single Number
// Given an array of integers, every element appears twice except for one.
// Find that single one.
//
// Note:
// Your algorithm should have a linear runtime complexity.
// Could you implement it without using extra memory?

#include <instream>

using namespace std;

class Solution {
public:
  int singleNumber(vector<int>& nums) {
    int res = 0;
    for (auto& element : nums) {
      res ^= element;
    }
    return res;
  }
};

int main() {
  return 0;
}
