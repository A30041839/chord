// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 5, 2014
// Update:     May 5, 2014
//
// Divide Two Integers
// Divide two integers without using multiplication, division and mod operator.

#include <iostream>

using namespace std;

class Solution {
  long long ll_divide(long long dividend, long long divisor) {
    long long res = 0;

    while (dividend >= divisor) { // >=
      long long div = divisor;
      long long bit = 1;
      while ((div << 1) <= dividend) {
        bit <<= 1;
        div <<= 1;
      }
      dividend -= div;
      res |= bit;
    }

    return res;
  }

public:
  int divide(int dividend, int divisor) {
    bool sign = (dividend < 0 && divisor < 0) || (dividend > 0 && divisor > 0);
    // Dont forget the cast, or it will be wrong
    long long ll_dividend = abs((long long)dividend);
    long long ll_divisor = abs((long long)divisor);

    long long res = ll_divide(ll_dividend, ll_divisor);
    res = sign ? res : -res;
    if (res > INT_MAX || res < INT_MIN) {
      return INT_MAX;
    }
    return res;
  }
};

int main() {
  return 0;
}
