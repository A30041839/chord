// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 5, 2014
// Update:     May 5, 2014
//
// 4Sum
// Given an array S of n integers, are there elements a, b, c in S such that 
// a + b + c = 0? 
// Find all unique triplets in the array which gives the sum of zero.
//
// Note:
// Given an array S of n integers, are there elements a, b, c, and d in S such
// that a + b + c + d = target? 
// Find all unique quadruplets in the array which gives the sum of target.
// Elements in a quadruplet (a,b,c,d) must be in non-descending order.
// (ie, a <= b <= c <= d)
// The solution set must not contain duplicate quadruplets.

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {

  // Time complexity is more than O(2*N^2*logN)
  vector<vector<int>> fourSum1(vector<int>& num, int target) {
    int n = num.size();
    if (n < 4) {
      return {};
    }

    //map<int, vector<pair<int, int>>> mp;
    unordered_map<int, vector<pair<int, int>>> mp;

    sort(num.begin(), num.end());
    //num.erase(unique(num.begin(), num.end()), num.end());
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        mp[num[i] + num[j]].push_back({i, j});
      }
    }

    vector<int> keys(mp.size(), 0);
    int idx = 0;
    for (auto& p : mp) {
      keys[idx++] = p.first;
    }
    sort(keys.begin(), keys.end());

    vector<vector<int>> res;
    int st = 0, ed = idx - 1;
    while (st <= ed) {
      int a = keys[st], b = keys[ed], sum = a + b;
      if (sum == target) {
        for (auto& i : mp[a]) {
          for (auto& j : mp[b]) {
            if (i.first == j.first || i.first == j.second
              || i.second == j.first || i.second == j.second) {
              continue;
            }
            vector<int> sub = {num[i.first], num[i.second], num[j.first], num[j.second]};
            sort(sub.begin(), sub.end());
            if (find(res.begin(), res.end(), sub) == res.end()) {
              res.push_back(sub);
            }
          }
        }
        ++st;
        --ed;
      } else if (sum > target) {
        --ed;
      } else {
        ++st;
      }
    }

    return res;
  }

  vector<vector<int>> fourSum2(vector<int>& num, int target) {
    int n = (int)num.size();
    if (n < 4) {
      return {};
    }

    vector<vector<int>> res;

    sort(num.begin(), num.end());
    for (int i = 0; i < n - 3; ++i) {
      if (i && num[i] == num[i - 1]) { // !!
        continue;
      }
      for (int j = i + 1; j < n - 2; ++j) {
        if (j > i + 1 && num[j] == num[j - 1]) { // !!
          continue;
        }
        int sum = target - num[i] - num[j];
        int st = j + 1, ed = n - 1;

        while (st < ed) {
          if (sum == num[st] + num[ed]) {
            res.push_back({num[i], num[j], num[st], num[ed]});
            while (st + 1 < ed && num[st + 1] == num[st]) { // !!
              ++st;
            }
            ++st;
            while (st < ed - 1 && num[ed - 1] == num[ed]) { // !!
              --ed;
            }
            --ed;
          } else if (sum > num[st] + num[ed]) {
            ++st;
          } else {
            --ed;
          }
        }
      }
    }

    return res;
  }

public:
  vector<vector<int> > fourSum(vector<int> &num, int target) {
    return fourSum1(num, target);
    //return fourSum2(num, target);
  }
};

int main() {
  vector<int> num = {0, 0, 0, 0};
  Solution sol;
  auto res = sol.fourSum(num, 0);
  cout << res.size() << endl;
  return 0;
}
