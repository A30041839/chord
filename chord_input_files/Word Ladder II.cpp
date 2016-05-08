// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Word Ladder II
// Given two words (start and end), and a dictionary, find all shortest
// transformation sequence(s) from start to end, such that:
// Only one letter can be changed at a time
// Each intermediate word must exist in the dictionary
// For example,
// 
// Given:
// start = "hit"
// end = "cog"
// dict = ["hot","dot","dog","lot","log"]
// Return
//   [
//     ["hit","hot","dot","dog","cog"],
//     ["hit","hot","lot","log","cog"]
//   ]
//
// Note:
// All words have the same length.
// All words contain only lowercase alphabetic characters.

#include "leetcode.h"

class Solution {
  void dfs(unordered_map<string, vector<string>>& mp, string cur, string start,
    vector<vector<string>>& res, vector<string>& seq) {
    if (cur == start) {
      // Don't reverse directly, it will change the first element
      res.push_back(vector<string>(seq.rbegin(), seq.rend()));
      return ;
    }

    for (string str : mp[cur]) {
      seq.push_back(str);
      dfs(mp, str, start, res, seq);
      seq.pop_back();
    }
  }

  vector<vector<string>> findLadders1(string start, string end,
    unordered_set<string>& dict) {
    unordered_map<string, vector<string>> mp;
    unordered_map<string, int> mark;
    queue<pair<string, int>> q;

    q.push({start, 0});
    dict.insert(end);
    mark[start] = 0;
    while (q.size()) {
      string cur = q.front().first;
      int step = q.front().second;
      q.pop();

      if (cur == end) {
        break;
      }
      for (int i = 0; i < cur.size(); ++i) {
        string next = cur;
        for (int j = 'a'; j <= 'z'; ++j) {
          next[i] = j;
          if (dict.count(next) && (mark.count(next) == 0 || step + 1 == mark[next])) {
            if (mark.count(next) == 0) {
              mark[next] = step + 1;
              // If `next` node has occurred in the queue, dont put it again
              q.push({next, step + 1});
            }
            mp[next].push_back(cur);
          }
        }
      }
    }

    vector<vector<string>> res;
    vector<string> seq = {end};

    dfs(mp, end, start, res, seq);

    return res;

  }
public:
  vector<vector<string>> findLadders(string start, string end,
    unordered_set<string> &dict) {
    return findLadders1(start, end, dict);
    // The second solution is compute the length first, then dfs all the paths
  }
};

int main() {
  return 0;
}
