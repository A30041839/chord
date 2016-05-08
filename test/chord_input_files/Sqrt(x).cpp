// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 9, 2014
// Updat:      May 9, 2014
//
// Sqrt(x) 
// Implement int sqrt(int x).
// Compute and return the square root of x.

#include "leetcode.h"

class Solution {
  int mySqrt1(int x) {
    int lo = 0, hi = x / 2;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      long long val = (long long)mid * mid;
      if (val == x) {
        return mid;
      }
      if (val < x) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }
    // Trick, but easy coding..
    for (int i = lo + 5; i > max(0, hi - 5); --i) {
      if ((long long)i * i <= x) {
        return i;
      }
    }
  }

  // Negative number have no sqrt()
  int mySqrt2(int x) {
    if (x < 0) {
      fprintf(stderr, "negative number.\n");
    }
    long long start = -1;
    long long end = (long long)x + 1; // !!

    // invariant relation is A[start] <= target < A[end]
    while (end - start > 1) {
      long long mid = start + (end - start) / 2;
      if (mid * mid > (long long)x) {
        end = mid;
      } else {
        start = mid;
      }
    }
    return (int)start;
  }

  int mySqrt3(int x) {
    if (x == 0) {
      return 0;
    }

    double cur = x, next;
    do {
      next = cur;
      cur = (cur + x / cur) / 2;
    } while (abs(cur - next) > 1e-9);

    return (int)cur;
  }

public:
  int mySqrt(int x) {
    //return mySqrt1(x);
    return mySqrt2(x);
    //return mySqrt3(x);
  }
};

int main() {
  return 0;
}
