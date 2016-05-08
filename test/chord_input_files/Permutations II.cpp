// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 8, 2014
// Update:     May 8, 2014
//
// Permutations II
// Given a collection of numbers that might contain duplicates, return all
// possible unique permutations.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  void dfs(const vector<int>& num, vector<vector<int>>& res, vector<int>& sub,
    vector<bool>& visit) {
    if (sub.size() == num.size()) {
      res.push_back(sub);
      return ;
    }

    int last = -1;
    for (int i = 0; i < (int)num.size(); ++i) {
      if (visit[i]) {
        continue;
      }
      // Each dfs() is a layer, assign a value to the sub[].
      // So this condition ensures only the distinctive value occur in current
      // dfs layer
      if (last != -1 && num[last] == num[i]) {
        continue;
      }
      sub.push_back(num[i]);
      visit[i] = true;
      dfs(num, res, sub, visit);
      visit[i] = false;
      sub.pop_back();
      last = i;
    }
  }

public:
  vector<vector<int>> permuteUnique(vector<int> &num) {
    vector<vector<int>> res;
    vector<int> sub;
    vector<bool> visit(num.size(), false);

    // Whether sort or not make the result huge difference, actully it makes 'MLE'
    // Think why?
    sort(num.begin(), num.end());
    dfs(num, res, sub, visit);

    return res;
  }
};

int main() {
  return 0;
}
