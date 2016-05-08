// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 17, 2014
// Update:     Aug 08, 2014
//
// Implement strStr()
// Returns a pointer to the first occurrence of needle in haystack, or null if 
// needle is not part of haystack.

#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
  int strStr1(string haystack, string needle) {
    if (needle.empty()) {
      return 0;
    }
    if (needle.size() > haystack.size()) {
      return -1;
    }
    int nh = haystack.size(), nn = needle.size();
    for (int i = 0; i + nn - 1 < nh; ++i) {
      int j = 0;
      for (; j < nn; ++j) {
        if (needle[j] != haystack[i + j]) {
          break;
        }
      }
      if (j == nn) {
        return i;
      }
    }

    return -1;
  }

  int strStr2(string haystack, string needle) {
    if (needle.empty()) {
      return 0;
    }
    if (haystack.size() < needle.size()) {
      return -1;
    }
    int nh = haystack.size(), nn = needle.size();
    vector<int> pre(nn, 0);
    getp(needle, pre);

    int j = -1;
    for (int i = 0; i < nh; ++i) {
      while (j != -1 && haystack[i] != needle[j + 1]) {
        j = pre[j];
      }
      if (haystack[i] == needle[j + 1]) {
        ++j;
      }
      if (j == nn - 1) {
        return i - nn + 1;
      }
    }
    return -1;
  }

  void getp(string& s, vector<int>& pre) {
    assert(s.size() == pre.size());
    int n = s.size();
    int j = -1;

    pre[0] = -1;
    for (int i = 1; i < n; ++i) {
      while (j != -1 && s[j + 1] != s[i]) {
        j = pre[j];
      }
      if (s[j + 1] == s[i]) {
        pre[i] = j + 1;
        ++j;
      } else {
        pre[i] = -1;
      }
    }
  }

public:

  int strStr(string haystack, string needle) {
    //return strStr1(haystack, needle);
    return strStr2(haystack, needle);
  }
};

/*
class Solution {
  char* strStr1(char *haystack, char *needle) {
    if (! haystack || ! needle) {
      return nullptr;
    }
    if (*needle == '\0') {
      return haystack;
    } else if (*haystack == '\0') {
      return nullptr;
    }

    while (true) {
      char* h = haystack, *n = needle;
      while (*h != '\0' && *n != '\0' && *h == *n) {
        ++h;
        ++n;
      }
      if (*n == '\0') {
        return haystack;
      }
      if (*h == '\0') { // prune!!
        return nullptr;
      }
      ++haystack;
    }
  }

  void findp(const char* s, vector<int>& pre) {
    int n = strlen(s), j = -1;
    pre.assign(n, 0);

    pre[0] = -1;
    for (int i = 1; i < n; ++i) {
      while (j != -1 && s[j + 1] != s[i]) {
        j = pre[j];
      }
      if (s[j + 1] == s[i]) {
        pre[i] = j + 1;
        ++j;
      } else {
        pre[i] = -1;
      }
    }
  }

  char* strStr2(char *haystack, char* needle) {
    if (! *needle) { // test only needle, since we need to get pre[]
      return haystack;
    }
    char* s = haystack, *p = needle;
    int n = strlen(s);
    int m = strlen(p);
    vector<int> pre;

    findp(p, pre);
    int j = -1;
    for (int i = 0; i < n; ++i) {
      while (j != -1 && s[i] != p[j + 1]) {
        j = pre[j];
      }
      if (s[i] == p[j + 1]) {
        ++j;
      }
      if (j == m - 1) {
        return haystack + (i - j);
      }
    }
    return nullptr;
  }

public:
  char *strStr(char *haystack, char *needle) {
    //return strStr1(haystack, needle);
    return strStr2(haystack, needle);
  }
};
*/

int main() {
  string haystack = "baabbbbababbbabab";
  string needle = "abbab";
  Solution sol;
  int pos = sol.strStr(haystack, needle);
  printf("%d\n", pos);

  return 0;
}
