// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Reverse Words in a String
// Given an input string, reverse the string word by word.
// For example,
// Given s = "the sky is blue",
// return "blue is sky the".
//
// Clarification:
// What constitutes a word?
// -- A sequence of non-space characters constitutes a word.
// Could the input string contain leading or trailing spaces?
// -- Yes. However, your reversed string should not contain leading or trailing spaces.
// How about multiple spaces between two words?
// -- Reduce them to a single space in the reversed string.

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
  void reverseWords1(string& s) {
    istringstream sin(s);
    vector<string> words;
    string str;

    while (sin >> str) {
      words.push_back(str);
    }

    ostringstream os;
    for (int i = words.size() - 1; i >= 0; --i) {
      os << words[i];
      if (i) {
        os << ' ';
      }
    }
    s = os.str();
  }

  void reverseWords2(string& s) {
    string res;

    int i = s.size() - 1;
    while (i >= 0) {
      while (i >= 0 && s[i] == ' ') {
        --i;
      }
      if (i < 0) {
        break;
      }
      string word;
      while (i >= 0 && s[i] != ' ') {
        word.push_back(s[i--]);
      }
      reverse(word.begin(), word.end());
      if (!res.empty()) {
        res.append(" ");
      }
      res.append(word);
    }

    s = res;
  }

  void reverseWords3(string& s) {
    int st = 0, ed = s.size() - 1;
    while (st <= ed && s[st] == ' ') {
      ++st;
    }
    while (ed >= st && s[ed] == ' ') {
      --ed;
    }
    if (st > ed) {
      s.clear();
      return ;
    }

    int count = 0;
    for (int i = st; i <= ed; ) {
      s[count++] = s[i];
      int j = i + 1;
      if (s[i] == ' ') {
        while (j <= ed && s[j] == ' ') {
          ++j;
        }
      }
      i = j;
    }
    s.resize(count);

    reverse(s.begin(), s.end());
    st = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
      if (s[i] == ' ') {
        reverse(s.begin() + st, s.begin() + i);
        st = i + 1;
      }
    }
    reverse(s.begin() + st, s.end());
  }

public:
  void reverseWords(string &s) {
    // reverseWords1(s);
    //reverseWords2(s);
    reverseWords3(s);
  }
};

int main() {
  Solution sol;
  string s = "hi!";
  sol.reverseWords(s);
  cout << s << endl;
  return 0;
}
