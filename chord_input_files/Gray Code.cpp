// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Date:       May 10, 2014
//
// Gray Code
// The gray code is a binary numeral system where two successive values differ
// in only one bit.
// Given a non-negative integer n representing the total number of bits in the
// code, print the
// sequence of gray code. A gray code sequence must begin with 0.
// For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
// 00 - 0
// 01 - 1
// 11 - 3
// 10 - 2
//
// Note:
// For a given n, a gray code sequence is not uniquely defined.
// For example, [0,2,3,1] is also a valid gray code sequence according to the
// above definition.
// For now, the judge is able to judge based on one instance of gray code
// sequence. Sorry about that.
//
// refer
// http://www.matrix67.com/blog/archives/266

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  // The i-th gray code equals to (i xor (i shr 1)).
  vector<int> grayCode1(int n) {
    vector<int> res(1 << n, 0);

    for (int i = 0; i < (1 << n); ++i) {
      res[i] = (i >> 1) ^ i ;
    }

    return res;
  }

  // Get the batch of gray code by 1, 2, 4, 8, ... each time by set the highest
  // position to 1 in each batch
  vector<int> grayCode2(int n) {
    vector<int> res(1 << n, 0);

    for (int i = 0; i < n; ++i) {
      int m = 1 << i;
      for (int j = 0; j < m; ++j) {
        res[m - j - 1] = res[j] | m;
      }
    }

    return res;
  }

public:
  vector<int> grayCode(int n) {
    //return grayCode1(n);
    return grayCode2(n);
  }
};

int main() {
  return 0;
}
