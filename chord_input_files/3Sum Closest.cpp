// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 4, 2014
// Updat:      May 4, 2014
//
// 3Sum Closest
// Given an array S of n integers, find three integers in S such that the sum is
// closest to 
// a given number, target. Return the sum of the three integers. 
// You may assume that each input would have exactly one solution.

#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
  void update1(int& res, int& dis, int target, int sum) {
    if (abs(sum - target) < dis) {
      dis = abs(sum - target);
      res = sum;
    }
  }

  int threeSumClosest1(vector<int>& num, int target) {
    int n = (int)num.size();
    int res = 0, dis = numeric_limits<int>::max();

    sort(num.begin(), num.end());
    for (int i = 0; i < n - 2; ++i) { // *
      for (int j = i + 1; j < n - 1; ++j) { // *
        int key = target - num[i] - num[j];
        int pos = lower_bound(num.begin() + j + 1, num.end(), key) - num.begin();
        update1(res, dis, target, num[i] + num[j] + num[max(j + 1, pos - 1)]);
        update1(res, dis, target, num[i] + num[j] + num[min(n - 1, pos)]);
      }
    }

    return res;
  }

  // !
  int threeSumClosest2(vector<int>& num, int target) {
    int n = (int)num.size();
    if (n < 3) {
      // Error
    }

    int res = num[0] + num[1] + num[2];

    sort(num.begin(), num.end());
    for (int i = 0; i < n - 2; ++i) {
      if (i && num[i] == num[i - 1]) {
        continue;
      }
      int st = i + 1, ed = n - 1;
      while (st < ed) {
        int sum = num[i] + num[st] + num[ed];
        if (sum == target) {
          return sum;
        } else {
          if (abs(sum - target) < abs(res - target)) {
            res = sum;
          }
          if (sum < target) {
            ++st;
          } else {
            --ed;
          }
        }
      }
    }

    return res;
  }

public:
  int threeSumClosest(vector<int>& num, int target) {
    //return threeSumClosest1(num, target);
    return threeSumClosest2(num, target);
  }
};

int main() {
  return 0;
}
