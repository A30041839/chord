// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     May 13, 2014
//
// Palindrome Number
// Determine whether an integer is a palindrome. Do this without extra space.
//
// Some hints:
// Could negative integers be palindromes? (ie, -1) (No!)
// If you are thinking of converting the integer to string, note the restriction
// of using extra space.
// You could also try reversing an integer. However, if you have solved the 
// problem "Reverse Integer", you know that the reversed integer might overflow.

#include <iostream>

class Solution {
  // Iterative solution
  bool isPalindrome1(int x) {
    if (x < 0) {
      return false;
    }

    long long base = 1;
    while (base * 10 <= x) { // !! =
      base *= 10;
    }

    while (x) {
      if (x / base != x % 10) {
        return false;
      }
      x = x % base / 10;
      base /= 100;
    }
    return true;
  }

  bool _isPalindrome2(int x, int d) {
    if (x == 0) { // !!
      return true;
    }
    return x / d == x % 10 and _isPalindrome2(x % d / 10, d / 100);
  }

  // Recursive solution
  bool isPalindrome2(int x) {
    if (x < 0) {
      return false;
    }
    int d = 1;
    while (x / d >= 10) {
      d *= 10;
    }
    return _isPalindrome2(x, d);
  }

public:
  bool isPalindrome(int x) {
    //return isPalindrome1(x);
    return isPalindrome2(x);
  }
};

int main() {
  return 0;
}
