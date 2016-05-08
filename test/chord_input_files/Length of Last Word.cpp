// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     May 13, 2014
//
// Length of Last Word
// Given a string s consists of upper/lower-case alphabets and empty space
// characters ' ', return the length of last word in the string.
// If the last word does not exist, return 0.
//
// Note:
// A word is defined as a character sequence consists of non-space characters only.
// For example,
// Given s = "Hello World",
// return 5.

#include <iostream>
#include <cstring>

using namespace std;

class Solution {
public:
  int lengthOfLastWord(string s) {
    if (s.empty()) {
      return 0;
    }
    int res = 0;

    for (int i = s.size() - 1; i >= 0; --i) {
      if (s[i] != ' ') {
        ++res;
      } else if (res > 0) {
        break;
      }
    }

    return res;
  }
};

int main() {
  return 0;
}
