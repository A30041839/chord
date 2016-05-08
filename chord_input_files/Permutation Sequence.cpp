// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 8, 2014
// Update:     May 8, 2014
//
// Permutation Sequence
// The set [1,2,3,...,n] contains a total of n! unique permutations.
// By listing and labeling all of the permutations in order,
// We get the following sequence (ie, for n = 3):
// "123"
// "132"
// "213"
// "231"
// "312"
// "321"
// Given n and k, return the kth permutation sequence.
//
// Note:
// Given n will be between 1 and 9 inclusive.

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  string getPermutation(int n, int k) {
    string num;
    int tot = 1;

    for (int i = 1; i <= n; ++i) {
      num.push_back(i + '0');
      tot *= i;
    }

    --k;
    string res;
    while (n) {
      tot /= n;
      res.push_back(num[k / tot]);
      num.erase(num.begin() + k / tot);
      k %= tot;
      --n;
    }

    return res;
  }
};

int main() {
  return 0;
}
