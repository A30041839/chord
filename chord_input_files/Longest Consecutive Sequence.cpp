// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 22, 2014
// Update:     Jul 03, 2014
//
// Longest Consecutive Sequence
// Given an unsorted array of integers, find the length of the longest
// consecutive elements sequence.
// For example,
// Given [100, 4, 200, 1, 3, 2],
// The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
// Your algorithm should run in O(n) complexity.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
  // The length of the consecutive segment is stored in the two ends.
  // The element between range[left, right] is not zeros also
  int merge(unordered_map<int, int>& ht, int a, int b) {
    int left = a - ht[a] + 1;
    int right = b + ht[b] - 1;
    return ht[left] = ht[right] = right - left + 1;
  }

  int longestConsecutive1(vector<int>& num) {
    if (num.size() == 0) {
      return 0;
    }
    unordered_map<int, int> ht;
    int res = 0;

    for (int& val : num) {
      if (ht[val]) {
        continue;
      }
      ht[val] = 1;
      res = max(res, 1);
      if (ht.count(val - 1)) {
        res = max(res, merge(ht, val - 1, val));
      }
      if (ht.count(val + 1)) {
        res = max(res, merge(ht, val, val + 1));
      }
    }

    return res;
  }

  int longestConsecutive2(vector<int>& num) {
    unordered_set<int> st;
    for (auto& it : num) {
      st.insert(it);
    }
    int res = 0;
    for (auto& it : num) {
      if (! st.count(it - 1)) {
        int val = it;
        int cnt = 0;
        while (st.count(val)) {
          ++val;
          ++cnt;
        }
        res = max(res, cnt);
      }
    }
    return res;
  }

public:
  int longestConsecutive(vector<int> &num) {
    //return longestConsecutive1(num);
    return longestConsecutive2(num);
  }
};

int main() {
  return 0;
}
