// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Two Sum
// Given an array of integers, find two numbers such that they add up to a
// specific target number.
// The function twoSum should return indices of the two numbers such that they add up to the target, 
// where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
//
// You may assume that each input would have exactly one solution.
// Input: numbers={2, 7, 11, 15}, target=9
// Output: index1=1, index2=2

#include "leetcode.h"

class Solution {
public:

  // hash
  vector<int> twoSum1(vector<int> &numbers, int target) {
    int n = (int)numbers.size();
    unordered_map<int, int> mp;

    for (int i = 0; i < n; ++i) {
      if (mp.count(target - numbers[i])) {
        vector<int> res = {mp[target - numbers[i]], i + 1};
        return res;
      } else {
        mp[numbers[i]] = i + 1;
      }
    }
  }

  // two pointers
  vector<int> twoSum2(vector<int> &numbers, int target) {
    int n = numbers.size();
    vector<int> id(n, 0);

    for (int i = 0; i < n; ++i) {
      id[i] = i;
    }
    sort(begin(id), end(id),
      [&numbers](const int& a, const int& b){ return numbers[a] < numbers[b]; });

    int start = 0, end = n - 1;
    while (start < end) {
      int sum = numbers[id[start]] + numbers[id[end]];
      if (sum == target) {
        return {min(id[start], id[end]) + 1, max(id[start], id[end]) + 1};
      } else {
        sum > target ? --end : ++start;
      }
    }
    return {};
  }

  vector<int> twoSum(vector<int> &numbers, int target) {
    //return twoSum1(numbers, target);
    return twoSum2(numbers, target);
  }
};

int main() {
  return 0;
}
