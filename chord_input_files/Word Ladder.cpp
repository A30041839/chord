// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Word Ladder
// Given two words (start and end), and a dictionary, find the length of shortest
// transformation sequence from start to end, such that:
// Only one letter can be changed at a time
// Each intermediate word must exist in the dictionary
// For example,
//
// Given:
// start = "hit"
// end = "cog"
// dict = ["hot","dot","dog","lot","log"]
// As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
// return its length 5.
//
// Note:
// Return 0 if there is no such transformation sequence.
// All words have the same length.
// All words contain only lowercase alphabetic characters.

#include "leetcode.h"

class Solution {

  int ladderLength1(string start, string end, unordered_set<string> &dict) {
    if (start == end) {
      return 0;
    }
    queue<pair<string, int>> q;
    q.push({start, 1});

    dict.insert(end);
    while (q.size()) {
      auto cur = q.front();
      q.pop();

      if (cur.first == end) {
        return cur.second;
      }

      for (int i = 0; i < cur.first.size(); ++i) {
        string next = cur.first;
        for (int j = 'a'; j <= 'z'; ++j) {
          next[i] = j;
          if (dict.count(next)) {
            dict.erase(next);
            q.push({next, cur.second + 1});
          }
        }
      }

    }
    return 0;
  }

public:
  int ladderLength(string start, string end, unordered_set<string> &dict) {
    return ladderLength1(start, end, dict);
  }
};

int main() {
  return 0;
}
