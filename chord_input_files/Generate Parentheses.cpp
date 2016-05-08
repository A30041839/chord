// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     May 17, 2014
//
// Generate Parentheses
// Given n pairs of parentheses, write a function to generate all combinations 
// of well-formed parentheses.
// For example, given n = 3, a solution set is:
// "((()))", "(()())", "(())()", "()(())", "()()()"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
  void generate(int nl, int nr, vector<string>& res, string& sub, int dep) {
    if (dep == sub.size()) {
      res.push_back(sub);
      return ;
    }

    // If there is '(' to match current ')'
    if (nl > 0 && nr >= nl) {
      sub[dep] = '(';
      generate(nl - 1, nr, res, sub, dep + 1);
    }
    // If there is '(' needed to match
    if (nr > 0 && nr >= nl) {
      sub[dep] = ')';
      generate(nl, nr - 1, res, sub, dep + 1);
    }
  }

public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    string sub(n + n, ' ');

    generate(n, n, res, sub, 0);

    return res;
  }
};

int main() {
  return 0;
}
