#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int removeDuplicates1(vector<int>& nums) {
    int i = 0, m = 0, n = (int)nums.size();
    while (i < n) {
      int j = i;
      while (j < n && nums[i] == nums[j]) {
        ++j;
      }
      nums[m++] = nums[i];
      i = j;
    }
    return m;
  }

  // !
  int removeDuplicates2(vector<int>& nums) {
    int m = 0, n = (int)nums.size();
    for (int i = 0; i < n; ++i) {
      if (i == 0 || nums[i] != nums[m - 1]) {
        nums[m++] = nums[i];
      }
    }
    return m;
  }

public:
  int removeDuplicates(vector<int>& nums) {
    //return removeDuplicates1(nums);
    return removeDuplicates2(nums);
  }
};

int main() {
  return 0;
}
