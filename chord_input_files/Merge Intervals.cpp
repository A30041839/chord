// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 23, 2014
// Update:     May 23, 2014
//
// Merge Intervals
// Given a collection of intervals, merge all overlapping intervals.
// For example,
// Given [1,3],[2,6],[8,10],[15,18],
// return [1,6],[8,10],[15,18].

#include "leetcode.h"

class Solution {
public:
  vector<Interval> merge(vector<Interval> &intervals) {
    if (intervals.empty()) {
      return {};
    }

    vector<Interval> res;
    int n = (int)intervals.size();

    auto cmp = [](const Interval& lhs, const Interval& rhs) {
      return lhs.start < rhs.start;
    };
    sort(intervals.begin(), intervals.end(), cmp);

    for (int i = 0; i < n; ) {
      int end = intervals[i].end;
      int j = i + 1;
      while (j < n && end >= intervals[j].start) {
        end = max(end, intervals[j].end);
        ++j;
      }
      res.push_back(Interval(intervals[i].start, end));
      i = j;
    }

    return res;
  }
};

int main() {
  return 0;
}
