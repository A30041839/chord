// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 23, 2014
// Update:     May 23, 2014
//
// Longest Palindromic Substring
// Given a string S, find the longest palindromic substring in S. You may assume
// that the maximum length of S is 1000, and there exists one unique longest
// palindromic substring.

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

class Solution {
  // O(N^2) space, O(N^2) time
  string longestPalindrome1(string s) {
    if (s.size() == 0) {
      return s;
    }
    int n = s.size();
    bool dp[n][n];
    int maxlen = 1, start = 0;

    for (int i = 0; i < n; ++i) {
      dp[i][i] = true;
    }
    for (int len = 2; len <= n; ++len) {
      for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;
        if (len == 2) {
          dp[i][j] = s[i] == s[j];
        } else {
          dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
        }
        if (dp[i][j] && len > maxlen) {
          maxlen = len;
          start = i;
        }
      }
    }

    return s.substr(start, maxlen);
  }

  // O(N^2) time, O(2N) space
  string longestPalindrome2(string s) {
    if (s.empty()) {
      return {};
    }
    int n = s.size();
    bool dp[2][n];
    int start = 0, maxlen = 1, cur = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = i; j >= 0; --j) {
        // If dp[][j] = true means s[j...i] is palindrome
        if (i == j || j + 1 == i) {
          dp[cur][j] = s[i] == s[j];
        } else {
          dp[cur][j] = s[i] == s[j] && dp[cur ^ 1][j + 1];
        }
        if (dp[cur][j] && i - j + 1 > maxlen) {
          maxlen = i - j + 1;
          start = j;
        }
      }
      cur ^= 1;
    }

    return s.substr(start, maxlen);
  }

  // O(N^2) time, O(N) space
  string longestPalindrome3(string s) {
    if (s.empty() || s.size() == 1) {
      return s;
    }

    int n = s.size();
    int len = 0, start = 0;
    vector<bool> is_palind(n, false);

    for (int i = 0; i < n; ++i) {
      is_palind[i] = true;
      for (int j = 0; j < i; ++j) {
        is_palind[j] = is_palind[j + 1] && s[j] == s[i];
        if (is_palind[j] && i - j + 1 > len) {
          len = i - j + 1;
          start = j;
        }
      }
    }

    return s.substr(start, len);
  }

  // O(N^2) time, O(1) space
  string longestPalindrome4(string s) {
    int n = s.size();
    int start = 0, maxlen = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 2; ++j) { // even, odd
        bool equal = true;
        for (int k = 0; i - k >= 0 && i + j + k < n && equal; ++k) {
          equal = s[i - k] == s[i + j + k];
          if (equal && 2 * k + j + 1 > maxlen) {
            maxlen = 2 * k + j + 1;
            start = i - k;
          }
        }
      }
    }

    return s.substr(start, maxlen);
  }


public:
  string longestPalindrome(string s) {
    //return longestPalindrome1(s);
    //return longestPalindrome2(s);
    //return longestPalindrome3(s);
    return longestPalindrome4(s);
  }
};

int main(){
  string s = "whdqcudjpisufnrtsyupwtnnbsvfptrcgvobbjglmpynebblpigaflpbezjvjgbmofejyjssdhbgghgrhzuplbeptpaecfdanhlylgusptlgobkqnulxvnwuzwauewcplnvcwowmbxxnhsdmgxtvbfgnuqdpxennqglgmspbagvmjcmzmbsuacxlqfxjggrwsnbblnnwisvmpwwhomyjylbtedzrptejjsaiqzprnadkjxeqfdpkddmbzokkegtypxaafodjdwirynzurzkjzrkufsokhcdkajwmqvhcbzcnysrbsfxhfvtodqabvbuosxtonbpmgoemcgkudandrioncjigbyizekiakmrfjvezuzddjxqyevyenuebfwugqelxwpirsoyixowcmtgosuggrkdciehktojageynqkazsqxraimeopcsjxcdtzhlbvtlvzytgblwkmbfwmggrkpioeofkrmfdgfwknrbaimhefpzckrzwdvddhdqujffwvtvfyjlimkljrsnnhudyejcrtrwvtsbkxaplchgbikscfcbhovlepdojmqybzhbiionyjxqsmquehkhzdiawfxunguhqhkxqdiiwsbuhosebxrpcstpklukjcsnnzpbylzaoyrmyjatuovmaqiwfdfwyhugbeehdzeozdrvcvghekusiahfxhlzclhbegdnvkzeoafodnqbtanfwixjzirnoaiqamjgkcapeopbzbgtxsjhqurbpbuduqjziznblrhxbydxsmtjdfeepntijqpkuwmqezkhnkwbvwgnkxmkyhlbfuwaslmjzlhocsgtoujabbexvxweigplmlewumcone";
  Solution sol;
  string res = sol.longestPalindrome(s);
  cout << res << endl;

  return 0;
}
