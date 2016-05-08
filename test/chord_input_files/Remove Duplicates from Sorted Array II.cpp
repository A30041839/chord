#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int removeDuplicates1(vector<int>& nums) {
    int i = 0, m = 0;
    while (i < (int)nums.size()) {
      int j = i;
      while (j < (int)nums.size() && nums[i] == nums[j]) {
        ++j;
      }
      if (j - i >= 2) {
        nums[m] = nums[m + 1] = nums[i];
        m += 2;
      } else {
        nums[m++] = nums[i];
      }
      i = j;
    }
    return m;
  }

  // !
  int removeDuplicates2(vector<int>& nums) {
    int n = (int)nums.size();
    if (n < 2) {
      return n;
    }

    int m = 2;
    for (int i = 2; i < n; ++i) {
      if (nums[i] != nums[m - 1] || nums[i] != nums[m - 2]) { // !!
        nums[m++] = nums[i];
      }
    }

    return m;
  }

public:
  int removeDuplicates(vector<int>& nums) {
    return removeDuplicates1(nums);
    //return removeDuplicates2(nums);
  }
};

int main() {
  return 0;
}
