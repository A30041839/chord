// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 17, 2014
//
// Climbing Stairs
// You are climbing a stair case. It takes n steps to reach to the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways can
// you climb to the top?

#include <iostream>

using namespace std;

class Solution {
  int climbStairs1(int n) {
    vector<int> dp(n, 0);

    dp[0] = 1;
    dp[1] = 2;
    for (int i = 2; i < n; ++i) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n - 1];
  }

  int climbStairs2(int n) {
    vector<int> dp(3, 0);

    dp[0] = 1;
    dp[1] = 2;
    for (int i = 2; i < n; ++i) {
      dp[2] = dp[0] + dp[1];
      dp[0] = dp[1];
      dp[1] = dp[2];
    }

    return dp[n < 3 ? n - 1 : 2];
  }

public:
  int climbStairs(int n) {
    // return climbStairs1(n);
    return climbStairs2(n);
  }
};

int main() {
  return 0;
}
