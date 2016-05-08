// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 4, 2014
// Update:     May 4, 2014
//
// Substring with Concatenation of All Words
// You are given a string, S, and a list of words, L, that are all of the same
// length. Find all 
// starting indices of substring(s) in S that is a concatenation of each word in
// L exactly once and without any intervening characters.
//
// For example, given:
// S: "barfoothefoobarman"
// L: ["foo", "bar"]
// You should return the indices: [0,9].
// (order does not matter).

#include "leetcode.h"

class Solution {
public:
  vector<int> findSubstring(string s, vector<string>& words) {
    int n = (int)s.size();
    int m = (int)words.size();
    if (m == 0 || m * (int)words[0].size() > n) {
      return {};
    }

    vector<int> res;
    unordered_map<string, int> dict;
    int len = m * words[0].size();

    for (auto& word : words) {
      ++dict[word];
    }

    for (int i = 0; i + len - 1 < n; ++i) { // !!
      unordered_map<string, int> count;
      int nword = 0;
      for (int j = i; j < i + len; j += words[0].size()) {
        string word = s.substr(j, words[0].size());
        if (!dict.count(word) || count[word] >= dict[word]) {
          break;
        }
        ++count[word];
        ++nword;
      }
      if (nword == m) {
        res.push_back(i);
      }
    }

    return res;
  }
};

int main() {
  vector<string> v = {"foo", "bar"};

  Solution sol;
  vector<int> res = sol.findSubstring("barfoothefoobarman", v);
  print_vector(res);

  return 0;
}
