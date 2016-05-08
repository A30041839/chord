// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Restore IP Addresses
// Given a string containing only digits, restore it by returning all possible 
// valid IP address combinations.
// 
// For example:
// Given "25525511135",
// 
// return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
  void _dfs(const string& s, int pos, int count, vector<string>& res,
    string ip) {
    if (count == 4) {
      if (pos == (int)s.size()) {
        res.push_back(ip);
      }
      return ;
    }

    if (count) {
      ip.push_back('.');
    }
    int num = 0;
    for (int i = pos; pos < (int)s.size(); ++i) {
      // "0" is ok, but "01", "04" are wrong
      if (i - pos > 0 && s[pos] == '0') {
        break;
      }
      num = num * 10 + (s[i] - '0');
      if (num > 255) {
        break;
      }
      ip.push_back(s[i]);
      _dfs(s, i + 1, count + 1, res, ip);
    }
  }

public:
  vector<string> restoreIpAddresses(string s) {
    if ((int)s.size() < 4) {
      return {};
    }

    vector<string> res;
    string ip;

    _dfs(s, 0, 0, res, ip);

    return res;
  }
};

int main() {
  return 0;
}
