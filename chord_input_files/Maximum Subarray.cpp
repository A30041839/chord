// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 20, 2014
// Update:     May 20, 2014
//
// Maximum Subarray
// Find the contiguous subarray within an array (containing at least one number)
// which has the largest sum.
// For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
// the contiguous subarray [4,−1,2,1] has the largest sum = 6.

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
  // O(n) space.
  int maxSubArray1(vector<int>& nums) {
    int n = (int)nums.size();
    if (n == 0) {
      return 0;
    }
    vector<int> dp(n, 0);
    int res = 0;

    res = dp[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      if (dp[i - 1] > 0) { // !!
        dp[i] = dp[i - 1] + nums[i];
      } else {
        dp[i] = nums[i];
      }
      res = max(res, dp[i]);
    }

    return res;
  }

  // O(1) space.
  int maxSubArray2(vector<int>& nums) {
    int n = (int)nums.size();
    if (n == 0) {
      return 0;
    }
    int res = nums[0], acc = 0;

    for (int i = 0; i < n; ++i) {
      acc = max(nums[i], acc + nums[i]);
      res = max(res, acc);
    }

    return res;
  }

  int _maxsub3(vector<int>& nums, int start, int end) {
    if (start > end) {
      return INT_MIN;
    }
    if (start == end) {
      return nums[start];
    }

    int mid = start + (end - start) / 2;
    int lmax = _maxsub3(nums, start, mid - 1);
    int rmax = _maxsub3(nums, mid + 1, end);

    int res = nums[mid], sum = nums[mid];
    for (int i = mid - 1; i >= start; --i) {
      sum += nums[i];
      res = max(res, sum);
    }
    sum = res;
    for (int i = mid + 1; i <= end; ++i) {
      sum += nums[i];
      res = max(res, sum);
    }

    return max(res, max(lmax, rmax));
  }

  int maxSubArray3(vector<int>& nums) {
    int n = (int)nums.size();
    if (n == 0) {
      return 0;
    }
    return _maxsub3(nums, 0, n - 1);
  }

public:
  int maxSubArray(vector<int>& nums) {
    // return maxSubArray1(nums);
    //  return maxSubArray2(nums);
    return maxSubArray3(nums);
  }
};

int main() {
  return 0;
}
