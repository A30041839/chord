// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Updat:      May 17, 2014
//
// Valid Palindrome
// Given a string, determine if it is a palindrome, considering only alphanumeric
// characters and ignoring cases.
//
// For example:
// "A man, a plan, a canal: Panama" is a palindrome.
// "race a car" is not a palindrome.

#include "leetcode.h"

class Solution {
  bool isPalindrome1(string s) {
    string ns;

    for (char chr : s) {
      if (isalpha(chr) || isdigit(chr)) {
        ns.push_back(tolower(chr));
      }
    }

    int start = 0, end = ns.size() - 1;
    while (start < end) {
      if (ns[start++] != ns[end--]) {
        return false;
      }
    }

    return true;
  }

  bool isPalindrome2(string s) {
    int start = 0, end = s.size() - 1;

    while (start < end) {
      while (start < end && !isalnum(s[start])) {
        ++start;
      }
      while (start < end && !isalnum(s[end])) {
        --end;
      }
      if (tolower(s[start]) != tolower(s[end])) {
        return false;
      }
      ++start, --end;
    }

    return true;
  }

public:
  bool isPalindrome(string s) {
    // return isPalindrome1(s);
    return isPalindrome2(s);
  }
};

int main() {
  return 0;
}
