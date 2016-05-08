// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Evaluate Reverse Polish Notation
// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
//
// Valid operators are +, -, *, /. Each operand may be an integer or another 
// expression.

#include <iostream>
#include <string>

using namespace std;

class Solution {
  int calc(const string& op, int rhs, int lhs) {
    int res = 0;
    if (op == "+") {
      res = rhs + lhs;
    } else if (op == "-") {
      res = rhs - lhs;
    } else if (op == "*") {
      res = rhs * lhs;
    } else if (op == "/") {
      res = rhs / lhs;
    }
    return res;
  }
public:
  int evalRPN(vector<string> &tokens) {
    stack<int> stk;

    for (string& s : tokens) {
      if (s == "+" || s == "-" || s == "*" || s == "/") {
        int lhs = stk.top();
        stk.pop();
        int rhs = stk.top();
        stk.pop();
        stk.push(calc(s, rhs, lhs));
      } else {
        stk.push(atoi(s.c_str()));
      }
    }

    return stk.top();
  }
};

int main() {
  return 0;
}
