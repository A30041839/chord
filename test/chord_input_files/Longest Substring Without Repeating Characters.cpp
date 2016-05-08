// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     Jul 09, 2014
//
// Longest Substring Without Repeating Characters
// Given a string, find the length of the longest substring without repeating 
// characters. 
// For example, the longest substring without repeating letters for "abcabcbb" 
// is "abc", which the length is 3. 
// For "bbbbb" the longest substring is "b", with the length of 1.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  int lengthOfLongestSubstring1(string s) {
    int st = 0, i = 0, res = 0;
    int n = (int)s.size();
    vector<bool> hash(256, false);

    while (i < n) {
      if (!hash[s[i]]) {
        hash[s[i]] = true;
      } else {
        while (st < i && s[st] != s[i]) {
          hash[s[st]] = false;
          ++st;
        }
        ++st;
      }
      res = max(res, i - st + 1);
      ++i;
    }

    return res;
  }

  int lengthOfLongestSubstring2(string s) {
    int n = s.size();
    int res = 0, begin = 0;
    vector<int> pos(256, -1);

    for (int i = 0; i < n; ++i) {
      begin = max(begin, pos[s[i]] + 1);
      pos[s[i]] = i;
      res = max(res, i - begin + 1);
    }
    return res;
  }

public:
  int lengthOfLongestSubstring(string s) {
    //return lengthOfLongestSubstring1(s);
    return lengthOfLongestSubstring2(s);
  }
};

int main() {
  return 0;
}
