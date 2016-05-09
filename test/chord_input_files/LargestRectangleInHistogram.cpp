// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Largest Rectangle in Histogram 
// Given n non-negative integers representing the histogram's bar height where 
// the width of each bar is 1, find the area of largest rectangle in the 
// histogram.

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
  int largestRectangleArea(vector<int> &height) {
    int n = height.size();
    vector<int> width(n, 0);
    stack<int> stk;
    int res = 0;

    for (int i = 0; i < n; ++i) {
      while (!stk.empty() && height[stk.top()] >= height[i]) {
        stk.pop();
      }
      width[i] = stk.empty() ? i + 1 : i - stk.top();
      stk.push(i);
    }

    while (!stk.empty()) {
      stk.pop();
    }

    for (int i = n - 1; i >= 0; --i) {
      while (!stk.empty() && height[stk.top()] >= height[i]) {
        stk.pop();
      }
      width[i] += stk.empty() ? n - i : stk.top() - i;
      --width[i];
      res = max(res, width[i] * height[i]);

      stk.push(i);
    }

    return res;
  }
};

int main() {
  return 0;
}
