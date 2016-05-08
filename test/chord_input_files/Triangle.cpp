// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 16, 2014
// Update:     May 16, 2014
//
// Triangle
// For example, given the following triangle
// [
//    [2],
//   [3,4],
//  [6,5,7],
// [4,1,8,3]
// ]
// The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

class Solution {
public:
  int minimumTotal(vector<vector<int> > &triangle) {
    if (triangle.empty() || triangle[0].empty()) {
      return 0;
    }
    int n = triangle.size();

    vector<int> dp(triangle[n - 1].begin(), triangle[n - 1].end());
    for (int i = n - 2; i >= 0; --i) {
      for (int j = 0; j < i + 1; ++j) {
        dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
      }
    }

    return dp[0];
  }
};

int main() {
  return 0;
}

