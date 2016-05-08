// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Text Justification
// Given an array of words and a length L, format the text such that each line 
// has exactly L characters and is fully (left and right) justified.
// You should pack your words in a greedy approach; that is, pack as many words
// as you can in each line. Pad extra spaces ' ' when necessary so that each
// line has exactly L characters.
//
// Extra spaces between words should be distributed as evenly as possible. If 
// the number of spaces on a line do not divide evenly between words, the empty
// slots on the left will be assigned more spaces than the slots on the right.
//
// For the last line of text, it should be left justified and no extra space is 
// inserted between words.

#include "leetcode.h"

class Solution {
public:
  vector<string> fullJustify(vector<string> &words, int maxWidth) {
    int n = words.size();
    vector<string> res;

    for (int i = 0; i < n; ) {
      int len = words[i].size(), j = i + 1;
      // From the second word, one space should be added
      while (j < n && len + (int)words[j].size() + 1 <= maxWidth) {
        len += words[j].size() + 1;
        ++j;
      }

      int m = j - i;
      // The initalization of gap and rem is to avoid the situation that there 
      // is only word in the line
      int gap = m == 1 ? maxWidth - words[i].size() : (maxWidth - len) / (m - 1) + 1;
      int rem = m == 1 ? 0 : (maxWidth - len) % (m - 1);

      string line;
      bool blast = j == n; // for the last line
      for (int k = 0; k < m; ++k) {
        line.append(words[i + k]);
        if (blast) {
          gap = k != m - 1 ? 1 : maxWidth - len;
          line.append(gap, ' ');
        } else if (k != m - 1 || m == 1) { // two situations
          line.append(gap + (rem > 0), ' ');
          --rem;
        }
      }
      res.push_back(line);

      i = j;
    }

    return res;
  }
};

int main() {
  return 0;
}
