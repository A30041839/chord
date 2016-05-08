// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 23, 2014
// Update:     May 23, 2014
//
// Integer to Roman
// Given an integer, convert it to a roman numeral.
// Input is guaranteed to be within the range from 1 to 3999.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string intToRoman(int num) {
    vector<string> roman = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    vector<int> integer = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};

    string res;

    int n = (int)integer.size();

    for (int i = n - 1; i >= 0; --i) {
      while (num >= integer[i]) {
        res.append(roman[i]);
        num -= integer[i];
      }
    }

    /*
    while (num > 0) {
      for (int i =  n - 1; i >= 0; --i) {
        if (num >= integer[i]) {
          num -= integer[i];
          res.append(roman[i]);
          break;
        }
      }
    }
    */

    return res;
  }
};

int main() {
  return 0;
}
