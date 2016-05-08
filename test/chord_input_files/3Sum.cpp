// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 4, 2014
// Update:     May 4, 2014
//
// 3Sum
// Given an array S of n integers, are there elements a, b, c in S such that 
// a + b + c = 0? 
// Find all unique triplets in the array which gives the sum of zero.
//
// Note:
// Elements in a triplet (a,b,c) must be in non-descending order. (ie, a <= b <= c)
// The solution set must not contain duplicate triplets.

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &num) {
    int n = (int)num.size();
    if (n < 3) {
      return {};
    }

    vector<vector<int>> res;

    sort(num.begin(), num.end());
    for (int i = 0; i < n - 2; ++i) {
      if (i && num[i] == num[i - 1]) { // in case of duplicates
        continue;
      }
      int st = i + 1, ed = n - 1;
      while (st < ed) {
        int sum = num[i] + num[st] + num[ed];
        if (sum == 0) {
          res.push_back({num[i], num[st], num[ed]});
          while (st + 1 < ed && num[st + 1] == num[st]) {
            ++st;
          }
          ++st;
          while (st < ed - 1 && num[ed - 1] == num[ed]) {
            --ed;
          }
          --ed;
        } else if (sum > 0) {
          --ed;
        } else {
          ++st;
        }
      }
    }

    return res;
  }
};

int main() {
  return 0;
}
