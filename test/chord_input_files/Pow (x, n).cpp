// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 30, 2014
// Update:     Oct 05, 2014
//
// Pow(x, n)
// Implement pow(x, n).

#include <iostream>

using namespace std;

class Solution {
  // Take n as the format of binary, say, (5)_10 = (101)_2;
  double pow_itr(double x, long long n) {
    double res = 1;
    while (n) {
      if (n & 1) {
        res *= x;
      }
      n >>= 1;
      x *= x;
    }
    return res;
  }

  // Iterative
  double pow1(double x, int n) {
    bool sign = n > 0;
    double res = pow_itr(x, n > 0 ? n : -(long long)n);
    return sign ? res : 1.0 / res;
  }

  double pow_rec(double x, long long n) {
    if (n == 1) {
      return x;
    }
    if (n & 1) {
      return x * pow_rec(x, n - 1);
    } else {
      double ret = pow_rec(x, n >> 1);
      return ret * ret;
    }
  }

  // Recursive
  double pow2(double x, int n) {
    if (n == 0) {
      return 1;
    }
    bool sign = true;
    if (n < 0) {
      sign = false;
    }
    double res = pow_rec(x, n > 0 ? n : -(long long)n);
    return sign ? res : 1. / res;
  }

public:
  double pow(double x, int n) {
    //return pow1(x, n);
    return pow2(x, n);
  }
};

int main() {
  return 0;
}
