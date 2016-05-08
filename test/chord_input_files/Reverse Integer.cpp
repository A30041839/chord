// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Reverse Integer
// Reverse digits of an integer.
// Example1: x = 123, return 321
// Example2: x = -123, return -321

#include <iostream>

using namespace std;

class Solution {
public:
  // Can handle positive and negative integer.
  int reverse(int x) {
    long long res = 0;

    while (x) {
      res = res * 10 + x % 10;
      x /= 10;
    }
    if (res > INT_MAX || res < INT_MIN) {
      return 0;
    }
    return res;
  }
};

int main() {
  return 0;
}
