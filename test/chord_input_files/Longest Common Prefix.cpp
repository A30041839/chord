// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     May 13, 2014
//
// Longest Common Prefix
// Write a function to find the longest common prefix string amongst an array 
// of strings.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    if (strs.empty()) {
      return {};
    }

    for (int i = 0; i < strs[0].size(); ++i) {
      for (int j = 0; j < strs.size(); ++j) {
        if (strs[j].size() < i + 1 || strs[0][i] != strs[j][i]) {
          return strs[0].substr(0, i);
        }
      }
    }

    return strs[0];
  }
};

int main() {
  return 0;
}
