// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 22, 2014
// Update:     May 22, 2014
//
// Best Time to Buy and Sell Stock III
// Say you have an array for which the ith element is the price of a given stock
// on day i.
// Design an algorithm to find the maximum profit. You may complete at most two
// transactions.
// 
// Note:
// You may not engage in multiple transactions at the same time (ie, you must 
// sell the stock before you buy again).

#include <iostream>
#include <vector>

using namespace std;

// A straight method is divide the array into two sub-arrays, then resolve it as
// the `Best Time to Buy and Sell Stock II`, but it will get TLE

class Solution {
public:
  // O(N) time
  int maxProfit(vector<int> &prices) {
    int n = (int)prices.size();
    if (n < 2) {
      return 0;
    }

    int left[n], right[n];
    int minval = prices[0], maxval = prices[n - 1];

    left[0] = right[n - 1] = 0;
    for (int i = 1; i < n; ++i) {
      left[i] = max(left[i - 1], prices[i] - minval);
      minval = min(minval, prices[i]);
    }
    for (int i = n - 2; i >= 0; --i) {
      right[i] = max(right[i + 1], maxval - prices[i]);
      maxval = max(maxval, prices[i]);
    }

    int res = 0;
    for (int i = 1; i < n - 1; ++i) {
      res = max(res, left[i] + right[i + 1]);
    }
    res = max(res, left[n - 1]); // *

    return res;
  }
};

int main() {
  return 0;
}
