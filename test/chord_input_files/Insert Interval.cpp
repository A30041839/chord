// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 23, 2014
// Update:     May 23, 2014
//
// Insert Interval
// Given a set of non-overlapping intervals, insert a new interval into the
// intervals (merge if necessary).
// You may assume that the intervals were initially sorted according to their 
// start times.

#include "leetcode.h"

class Solution {

  bool intersect(const Interval& lhs, const Interval& rhs) {
    if (lhs.end < rhs.start || lhs.start > rhs.end) {
      return false;
    }
    return true;
  }

public:
  vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
    if (intervals.empty()) {
      return {newInterval};
    }
    auto cmp = [](const Interval& lhs, const Interval& rhs) {
      return lhs.start < rhs.start;
    };
    sort(intervals.begin(), intervals.end(), cmp);

    vector<Interval> res;
    bool merged = false;
    for (auto& ele : intervals) {
      if (!merged && intersect(ele, newInterval)) {
        newInterval.start = min(newInterval.start, ele.start);
        newInterval.end = max(newInterval.end, ele.end);
        continue;
      }
      if (!merged && newInterval.end < ele.start) {
        res.push_back(newInterval);
        merged = true;
      }

      res.push_back(ele);
    }
    if (!merged) {
      res.push_back(newInterval);
    }

    return res;
  }
};

int main() {
  return 0;
}
