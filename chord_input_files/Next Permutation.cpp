// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 7, 2014
// Update:     May 7, 2014
//
// Next Permutation
// Implement next permutation, which rearranges numbers into the lexicographically
// next greater permutation of numbers.
// If such arrangement is not possible, it must rearrange it as the lowest
// possible order (ie, sorted in ascending order).
// The replacement must be in-place, do not allocate extra memory.
// Here are some examples. Inputs are in the left-hand column and its
// corresponding outputs are in the right-hand column.
// 1,2,3 -> 1,3,2
// 3,2,1 -> 1,2,3
// 1,1,5 -> 1,5,1
//
// Solution: O(n)
// Take A = {1,3,2} for example:
// 1. Traverse from back to forth, find the turning point, that is A[i] = 3.
// 2. Sort from the turning point to the end (A[i] to A[end]), so {3,2} becomes {2,3}.
// 3. If i equals to 0, finish! Else, goto 4.
// 4. Let j = i, search from A[j] to A[end] to find the first elem which is larger than A[i-1], '2' here.
// 5. Swap the elem A[j] with A[i-1].
// 6. Finally, the next permutation is {2,1,3}.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void nextPermutation(vector<int> &num) {
    if (num.size() < 2) {
      return ;
    }
    int i = num.size() - 1;

    // Since the array may contain replicated elements, we utilize `<=` instead
    // of '<'
    while (i > 0 && num[i] <= num[i - 1]) {
      --i;
    }
    reverse(num.begin() + i, num.end());
    if (i == 0) {
      return ;
    }

    int j = i;
    // `<=`
    while (j < num.size() && num[j] <= num[i - 1]) {
      ++j;
    }
    swap(num[i - 1], num[j]);
  }
};

int main() {
  return 0;
}
