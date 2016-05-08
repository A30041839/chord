// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 5, 2014
//
// Add Binary
// Given two binary strings, return their sum (also a binary string).

#include <iostream>
#include <string>

using namespace std;

class Solution {
  string addBinary1(string a, string b) {
    int n = a.size();
    int m = b.size();
    string res(max(n, m), ' ');

    int i = n - 1, j = m - 1, k = res.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0) {
      int sum = carry;
      if (i >= 0) {
        sum += a[i--] - '0';
      }
      if (j >= 0) {
        sum += b[j--] - '0';
      }
      res[k--] = sum % 2 + '0';
      carry = sum / 2;
    }
    if (carry) {
      res.insert(res.begin(), '1');
    }

    return res;
  }

public:
  string addBinary(string a, string b) {
    return addBinary1(a, b);
  }
};

int main() {
  return 0;
}
