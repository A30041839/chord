// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 6, 2014
// Update:     May 6, 2014
//
// Multiply Strings
// Given two numbers represented as strings, return multiplication of the numbers
// as a string.
//
// Note:
// The numbers can be arbitrarily large and are non-negative.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
  string multiply1(string num1, string num2) {
    int n = num1.size();
    int m = num2.size();
    string res(n + m, '0');

    for (int i = n - 1; i >= 0; --i) {
      for (int j = m - 1; j >= 0; --j) {
        int sum = res[i + j + 1] - '0' + (num1[i] - '0') * (num2[j] - '0');
        res[i + j + 1] = sum % 10 + '0'; // !!
        res[i + j] += sum / 10;
      }
    }

    while (res.size() > 1 && res[0] == '0') { // !!
      res.erase(res.begin());
    }

    return res;
  }

public:
  string multiply(string num1, string num2) {
    return multiply1(num1, num2);
  }
};

int main() {
  Solution sol;
  string res = sol.multiply("9", "98");
  cout << res << endl;
  return 0;
}
