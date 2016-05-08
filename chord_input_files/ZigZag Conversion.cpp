// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// ZigZag Conversion
// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
// of rows like this: (you may want to display this pattern in a fixed font for
// better legibility)
//
// P   A   H   N
// A P L S I I G
// Y   I   R
//
// And then read line by line: "PAHNAPLSIIGYIR"
// Write the code that will take a string and make this conversion given a number of rows:
//
// string convert(string text, int nRows);
// convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

#include "leetcode.h"

class Solution {
public:
  string convert(string s, int nRows) {
    if (nRows == 1) {
      return s;
    }
      cout << "#" << endl;
    string res;
    int n = s.size();

    for (int row = 0; row < nRows; ++row) {
      for (int i = row; i < n; i += (nRows - 1) * 2) {
        res += s[i];
        if (row != 0 && row != nRows - 1) {
          if (i + (nRows - row - 1) * 2 < n) {
            res += s[i + (nRows - row - 1) * 2];
          }
        }
      }
    }

    return res;
  }
};

int main() {
  Solution sol;

  string res = sol.convert("A", 1);
  cout << res << endl;

  return 0;
}
