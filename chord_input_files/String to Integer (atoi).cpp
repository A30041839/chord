// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// String to Integer (atoi)
// Implement atoi to convert a string to an integer.
// Hint: Carefully consider all possible input cases. If you want a challenge,
// please do not see below and ask yourself what are the possible input cases.
//
// Notes:
// It is intended for this problem to be specified vaguely (ie, no given input
// specs).
// You are responsible to gather all the input requirements up front.

#include "leetcode.h"

class Solution {
public:
  int myAtoi(string str) {
    if (str.empty()) {
      return 0;
    }
    int n = str.size();
    int i = 0;

    long long res = 0;
    while (isspace(str[i])) {
      ++i;
    }

    int flag = 1;
    if (str[i] == '+' || str[i] == '-') {
      flag = str[i] == '+' ? 1 : -1;
      ++i;
    }

    while (i < n) {
      if (!isdigit(str[i])) {
        return res * flag;
      }
      res = res * 10 + str[i] - '0';
      if (res * flag > INT_MAX || res * flag < INT_MIN) {
        return flag > 0 ? INT_MAX : INT_MIN;
      }
      ++i;
    }

    return res * flag;
  }
};

int main() {
  return 0;
}
