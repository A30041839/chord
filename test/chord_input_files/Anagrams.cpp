// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 17, 2014
//
// Anagrams
// Given an array of strings, return all groups of strings that are anagrams.
//
// Note:
// All inputs will be in lower-case.

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
  vector<string> anagrams(vector<string> &strs) {
    vector<string> res;
    unordered_map<string, vector<int>> mp;

    for (int i = 0; i < (int)strs.size(); ++i) {
      string str = strs[i];
      // Any other hash methods is ok
      sort(str.begin(), str.end());
      mp[str].push_back(i);
    }

    for (auto& pair : mp) {
      if (pair.second.size() > 1) {
        for (auto& idx : pair.second) {
          res.push_back(strs[idx]);
        }
      }
    }

    return res;
  }
};

int main() {
  return 0;
}
