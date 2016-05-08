// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Longest Valid Parentheses
// Given a string containing just the characters '(' and ')', find the length of
// the longest valid (well-formed) parentheses substring.
//
// For "(()", the longest valid parentheses substring is "()", which has length 
// = 2.
//
// Another example is ")()())", where the longest valid parentheses substring is
// "()()", which has length = 4.

#include <iostream>

using namespace std;

class Solution {
  int longestValidParentheses1(string s) {
    int n = (int)s.size();
    int res = 0;

    int len = 0, m = 0;
    // Cannot handle such case: (()
    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        ++m;
      } else {
        --m;
      }
      ++len;
      if (m == 0 && len > res) {
        res = len;
      } else if (m < 0) {
        len = m = 0;
      }
    }

    len = m = 0;
    // Cannot handle such case: ())
    for (int i = n - 1; i >= 0; --i) {
      if (s[i] == ')') {
        ++m;
      } else {
        --m;
      }
      ++len;
      if (m == 0 && len > res) {
        res = len;
      } else if (m < 0) {
        len = m = 0;
      }
    }

    return res;
  }

public:
  int longestValidParentheses(string s) {
    return longestValidParentheses1(s);
  }
};

int main() {
  return 0;
}
