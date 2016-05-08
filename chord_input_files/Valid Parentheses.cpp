// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     May 13, 2014
//
// Valid Parentheses
// Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
// determine if the input string is valid.
// The brackets must close in the correct order, "()" and "()[]{}" are all valid 
// but "(]" and "([)]" are not.

#include "leetcode.h"

class Solution {
  bool is_match(char ca, char cb) {
    return ca == '(' && cb == ')' || ca == '[' && cb == ']' ||
      ca == '{' && cb == '}';
  }
public:
  bool isValid(string s) {
    stack<char> stk;

    for (auto& chr : s) {
      if (chr == '(' or chr == '[' or chr == '{') {
        stk.push(chr);
      } else if (stk.size()) {
        if (is_match(stk.top(), chr)) {
          stk.pop();
        } else {
          return false;
        }
      } else {
        return false;
      }
    }
    return stk.empty();
  }
};

int main() {
  return 0;
}
