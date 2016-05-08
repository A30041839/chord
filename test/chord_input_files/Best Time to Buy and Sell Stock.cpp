// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 21, 2014
// Update:     May 21, 2014
//
// Best Time to Buy and Sell Stock
// Say you have an array for which the ith element is the price of a given stock
// on day i.
// If you were only permitted to complete at most one transaction (ie, buy one
// and sell one share of the stock), design an algorithm to find the maximum profit.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &p) {
    if (p.size() < 2) {
      return 0;
    }
    int res = 0, buy = p[0];

    for (auto& stock : p) {
      res = max(res, stock - buy);
      buy = min(buy, stock);
    }
    return res;
  }
};

int main() {
}
