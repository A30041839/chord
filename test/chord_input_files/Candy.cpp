// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     Jul 08, 2014
//
// Candy
// There are N children standing in a line. Each child is assigned a rating value.
// You are giving candies to these children subjected to the following
// requirements:
//
// Each child must have at least one candy.
// Children with a higher rating get more candies than their neighbors.
// What is the minimum candies you must give?

#include <vector>

using namespace std;
class Solution {

  // O(N) time, O(N) space
  int candy1(vector<int>& ratings) {
    if (ratings.empty()) {
      return 0;
    }
    int n = ratings.size();
    vector<int> candy(n, 0);

    for (int i = n - 2; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) {
        candy[i] = candy[i + 1] + 1;
      }
    }
    int res = candy[0];
    for (int i = 1; i < n; ++i) {
      if (ratings[i] > ratings[i - 1] && candy[i] <= candy[i - 1]) {
        candy[i] = candy[i - 1] + 1;
      }
      res += candy[i];
    }

    return res + n;
  }

  // O(N) time, O(1) space

public:
  int candy(vector<int> &ratings) {
    return candy1(ratings);
  }
};

int main() {
  return 0;
}
