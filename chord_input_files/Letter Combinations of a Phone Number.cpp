// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Letter Combinations of a Phone Number
// Given a digit string, return all possible letter combinations that the number
// could represent.
// A mapping of digit to letters (just like on the telephone buttons) is given below.
//
// Note:
// Although the above answer is in lexicographical order, your answer could be
// in any order you want.

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Solution {
  static const vector<string> mp;

  void letterCombinationsHelper1(const string& digits, vector<string>& res,
    string& sub, int dep) {
    if (dep == (int)digits.size()) {
      if (!sub.empty()) {
        res.push_back(sub);
      }
      return ;
    }

    for (auto& c : mp[digits[dep] - '0']) {
      sub[dep] = c;
      letterCombinationsHelper1(digits, res, sub, dep + 1);
    }
  }

  vector<string> letterCombinations1(string digits) {
    vector<string> res;
    string sub(digits.size(), ' ');

    letterCombinationsHelper1(digits, res, sub, 0);

    return res;
  }

  vector<string> letterCombinations2(string digits) {
    if (digits.empty()) {
      return {};
    }
    vector<string> res;

    auto next = letterCombinations2(digits.substr(1));
    for (auto& fst : mp[digits[0] - '0']) {
      string sub = string(1, fst);
      if (!next.empty()) {
        for (auto& str : next) {
          res.push_back(sub + str);
        }
      } else {
        res.push_back(sub);
      }
    }

    return res;
  }

public:
  vector<string> letterCombinations(string digits) {
    //return letterCombinations1(digits);
    return letterCombinations2(digits);
  }
};

const vector<string> Solution::mp = {"", "", "abc", "def", "ghi", "jkl", "mno",
  "pqrs", "tuv", "wxyz"};

int main() {
  Solution sol;
  auto res = sol.letterCombinations("");
  for (auto& comb : res) {
    cout << comb << endl;
  }
  return 0;
}
