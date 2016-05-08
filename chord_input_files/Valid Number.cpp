// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 29, 2014
// Updat:      Jun 23, 2014
//
// Valid Number
// Validate if a given string is numeric.
//
// Some examples:
// "0" => true
// " 0.1 " => true
// "abc" => false
// "1 a" => false
// "2e10" => true
// Note: It is intended for the problem statement to be ambiguous. You should
// gather all requirements up front before implementing one.

#include "leetcode.h"
#include <regex>

class Solution {
  // TODO
  // DFA
  bool isNumber1(const char* s) {
    return true;
  }

  bool isNumber2(string s) {
    regex reg("^[+-]?(\d+\.?|\d*\.?\d+)([Ee][+-]?\d+|\d*)$");
    string str = s;

    return regex_match(str, reg);
  }

  bool has_sign(string s) {
    if (s.size() > 0 && (s[0] == '-' || s[0] == '+')) {
      return true;
    }
    return false;
  }

  bool is_int(string s) {
    if (s.empty()) {
      return false;
    }
    if (has_sign(s)) {
      s = s.substr(1);
    }
    return is_unsign_int(s);
  }

  bool is_unsign_int(string s) {
    if (s.empty() || has_sign(s)) {
      return false;
    }
    for (char& c : s) {
      if (!isdigit(c)) {
        return false;
      }
    }
    return true;
  }

  bool is_float(string s) {
    if (s.empty()) {
      return false;
    }
    s = has_sign(s) ? s.substr(1) : s;
    int pos = s.find('.');
    if (pos == -1) {
        return false;
    }
    string s1 = s.substr(0, pos), s2 = s.substr(pos + 1);
    int n1 = s1.size(), n2 = s2.size();
    bool bint1 = is_int(s1), bint2 = is_unsign_int(s2);
    return (!n1 && bint2) || (bint1 && bint2) || (bint1 && !n2);
  }

  bool is_scientific(string s) {
    if (s.empty()) {
      return false;
    }
    int pos = s.find('e');
    if (pos == -1) {
      pos = s.find('E');
    }
    if (pos == -1) {
      return false;
    }
    string s1 = s.substr(0, pos), s2 = s.substr(pos + 1);
    int n1 = s1.size(), n2 = s2.size();
    if ((!n1) || (!n2)) {
      return false;
    }
    return (is_int(s1) || is_float(s1)) && is_int(s2);
  }

  bool isNumber3(string s) {
    int start = 0, end = s.size() - 1;
    while (start < s.size() and s[start] == ' ') {
      ++start;
    }
    while (end > start and s[end] == ' ') {
      --end;
    }
    if (start == end) {
      return isdigit(s[start]);
    }
    s = s.substr(start, end - start + 1);

    if (has_sign(s)) {
      s = s.substr(1);
    }
    return is_int(s) || is_scientific(s) || is_float(s);
  }

public:
  bool isNumber(string s) {
    //return isNumber1(s);
    //return isNumber2(s);
    return isNumber3(s);
  }
};

int main() {
  vector<string> cases = {".", ".2", "12", "12.4", "0.2", "1e3", "1.2e8", "1.2e-1"
    , "-12.2", "-12e9", "-9e0.3", ".-4"};
  Solution sol;
  for (string& s : cases) {
    bool res = sol.isNumber(s.c_str());
    cout << s << " -> " << res << endl;
  }

  return 0;
}
