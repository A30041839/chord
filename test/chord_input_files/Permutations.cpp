// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 8, 2014
// Update:     May 8, 2014
//
// Permutations
// Given a collection of numbers, return all possible permutations.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  vector<vector<int>> permute1(vector<int> &num) {
    vector<vector<int>> res;
    sort(num.begin(), num.end());

    do {
      res.push_back(num);
    } while (next_permutation(num.begin(), num.end()));

    return res;
  }

  bool next_permutation2(vector<int>& num) {
    int i = num.size() - 1;
    while (i > 0 && num[i] <= num[i - 1]) {
      --i;
    }
    reverse(num.begin() + i, num.end());
    if (i == 0) {
      return false;
    }
    int j = i;
    while (j < num.size() && num[j] <= num[i - 1]) {
      ++j;
    }
    swap(num[j], num[i - 1]);
    return true;
  }

  vector<vector<int>> permute2(vector<int> &num) {
    vector<vector<int>> res;
    sort(num.begin(), num.end());

    do {
      res.push_back(num);
    } while (next_permutation2(num));

    return res;
  }

  void dfs3(const vector<int>& num, vector<vector<int>>& res, 
    vector<int>& sub, vector<bool>& visit) {
    if (sub.size() == num.size()) {
      res.push_back(sub);
      return ;
    }

    for (int i = 0; i < num.size(); ++i) {
      if (!visit[i]) {
        visit[i] = true;
        sub.push_back(num[i]);
        dfs3(num, res, sub, visit);
        visit[i] = false;
        sub.pop_back();
      }
    }
  }

  vector<vector<int>> permute3(vector<int> &num) {
    vector<vector<int>> res;
    vector<int> sub;
    vector<bool> visit(num.size(), false);

    sort(num.begin(), num.end());
    dfs3(num, res, sub, visit);

    return res;
  }

public:
  vector<vector<int>> permute(vector<int> &num) {
    //return permute1(num);
    //return permute2(num);
    return permute3(num);
  }
};

int main() {
  return 0;
}
