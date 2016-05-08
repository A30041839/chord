// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     Jul 7, 2014
//
// Minimum Window Substring
// Given a string S and a string T, find the minimum window in S which will
// contain all the characters in T in complexity O(n).
//
// For example,
// S = "ADOBECODEBANC"
// T = "ABC"
// Minimum window is "BANC".
//
// Note:
// If there is no such window in S that covers all characters in T, return the
// emtpy string "".
// If there are multiple such windows, you are guaranteed that there will always
// be only one unique minimum window in S.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
  string minWindow(string s, string t) {
    if (s.empty() || t.empty()) {
      return "";
    }
    vector<int> need(256, 0), actual(256, 0);
    int sn = s.size(), tn = t.size();
    int n_need = 0, res_start = 0, len = -1;

    for (auto& c : t) {
      ++need[c];
    }

    for (int start = 0, i = 0; i < sn; ++i) {
      if (actual[s[i]] < need[s[i]]) {
        ++n_need;
      }
      ++actual[s[i]];
      if (n_need >= tn) {
        while (start < i && actual[s[start]] > need[s[start]]) {
          --actual[s[start]];
          ++start;
        }
        if (len == -1 || i - start + 1 < len) {
          len = i - start + 1;
          res_start = start;
        }
      }
    }

    return len == -1 ? "" : s.substr(res_start, len);
  }
};

int main() {
  return 0;
}
