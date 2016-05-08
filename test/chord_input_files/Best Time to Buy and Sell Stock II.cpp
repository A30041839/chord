// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 22, 2014
// Update:     May 22, 2014
//
// Best Time to Buy and Sell Stock II
// Say you have an array for which the ith element is the price of a given stock
// on day i.
// Design an algorithm to find the maximum profit. You may complete as many
// transactions as you like (ie, buy one and sell one share of the stock
// multiple times). However, you may not engage in multiple transactions at the
// same time (ie, you must sell the stock before you buy again).

#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
  int maxProfit1(vector<int>& prices) {
    int n = (int)prices.size();
    if (n < 2) {
      return 0;
    }

    int res = 0, buy = prices[0];
    for (int i = 1; i < n; ++i) {
      bool tag = false;
      if ((i < n - 1 && prices[i + 1] < prices[i]) || (i == n - 1)) {
        if (prices[i] > buy) {
          res += prices[i] - buy;
          tag = true;
        }
      }
      buy = tag ? prices[i] : min(buy, prices[i]);
    }

    return res;
  }

  int maxProfit2(vector<int>& prices) {
    int res = 0;

    for (int i = 1; i < (int)prices.size(); ++i) {
      res += max(0, prices[i] - prices[i - 1]);
    }

    return res;
  }

public:
  int maxProfit(vector<int>& prices) {
    //return maxProfit1(prices);
    return maxProfit2(prices);
  }
};

int main() {
  return 0;
}
