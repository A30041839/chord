// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 5, 2014
// Update:     May 5, 2014
//
// Count and Say
// The count-and-say sequence is the sequence of integers beginning as follows:
// 1, 11, 21, 1211, 111221, ...
//
// 1 is read off as "one 1" or 11.
// 11 is read off as "two 1s" or 21.
// 21 is read off as "one 2, then one 1" or 1211.
// Given an integer n, generate the nth sequence.
//
// Note:
// The sequence of integers will be represented as a string.

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
  string countAndSay(int n) {
    string res = "1";

    while (--n) { // not `n--`
      int m = res.size();
      ostringstream os;
      for (int i = 0; i < m; ) {
        int j = i;
        while (j < m && res[j] == res[i]) {
          ++j;
        }
        os << (j - i) << res[i];
        i = j;
      }
      res = os.str();
    }

    return res;
  }
};

int main() {
  return 0;
}
