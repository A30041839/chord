// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 23, 2014
// Update:     May 23, 2014
//
// Roman to Integer
// Given a roman numeral, convert it to an integer.
// Input is guaranteed to be within the range from 1 to 3999.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int romanToInt(string s) {
    vector<string> roman = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    vector<int> integer = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};

    int n = (int)integer.size();
    int res = 0, st = 0;
    for (int i = n - 1; i >= 0; --i) {
      while (roman[i] == s.substr(st, roman[i].size())) {
        res += integer[i];
        st += roman[i].size();
      }
    }

    return res;
  }
};

int main() {
  return 0;
}
