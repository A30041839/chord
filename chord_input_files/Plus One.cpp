// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Plus One
// Given a number represented as an array of digits, plus one to the number.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  vector<int> plusOne(vector<int> &digits) {
    int n = digits.size();
    vector<int> res(n, 0);
    int carry = 1;

    for (int i = n - 1; i >= 0; --i) {
      int sum = carry + digits[i];
      res[i] = sum % 10;
      carry = sum / 10;
    }
    if (carry) {
      res.insert(res.begin(), 1);
    }

    return res;
  }
};

int main() {
  return 0;
}
