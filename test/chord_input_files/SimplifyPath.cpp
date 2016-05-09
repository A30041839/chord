// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Simplify Path
// Given an absolute path for a file (Unix-style), simplify it.
// 
// For example,
// path = "/home/", => "/home"
// path = "/a/./b/../../c/", => "/c"

#include "leetcode.h"

class Solution {
public:
  string simplifyPath(string path) {
    for (int i = 0; i < path.length(); ++i) {
      if (path[i] == '/') {
        path[i] = ' ';
      }
    }

    istringstream sin(path);
    stack<string> stk;
    string str;
    while (sin >> str) {
      if (str == "..") {
        if (stk.size()) {
          stk.pop();
        }
      } else if (str != ".") {
        stk.push(str);
      }
    }

    path.clear();
    while (!stk.empty()) {
      path = "/" + stk.top() + path;
      stk.pop();
    }

    return path.empty() ? "/" : path;
  }
};

int main() {
  return 0;
}
