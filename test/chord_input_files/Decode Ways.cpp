// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Decode Ways
// A message containing letters from A-Z is being encoded to numbers using the
// following mapping:
// 'A' -> 1
// 'B' -> 2
// ...
// 'Z' -> 26
// Given an encoded message containing digits, determine the total number of ways
// to decode it.
//
// For example,
// Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
// The number of ways decoding "12" is 2.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
  int numDecodings(string s) {
    if (s.empty()) {
      return 0;
    }

    int n = (int)s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      int num = s[i - 1] - '0';
      if (num == 0 && (i == 1 || s[i - 2] == '0' || s[i - 2] > '2')) {
        return 0;
      }

      if (num > 0) {
        dp[i] += dp[i - 1];
      }

      if (i > 1) {
        num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
        if (num >= 10 && num <= 26) {
          dp[i] += dp[i - 2];
        }
      }
    }

    return dp[n];
  }
};

int main() {
  return 0;
}
