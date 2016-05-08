// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 30, 2014
// Update:     May 30, 2014
//
// Median of Two Sorted Arrays
// There are two sorted arrays A and B of size m and n respectively. Find the
// median of the two sorted arrays. The overall run time complexity should be 
// O(log (m+n)).

#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {

  typedef vector<int>::iterator ITER;

  int _find(ITER nums1, int n, ITER nums2, int m, int pos) {
    // Make nums1 shorter and avoid overflow in the following code.
    if (n > m) {
      return _find(nums2, m, nums1, n, pos);
    }
    if (n == 0) {
      return *(nums2 + pos - 1);
    }
    if (pos == 1) {
      return min(*nums1, *nums2);
    }

    int i = min(n, pos / 2);
    int j = pos - i;
    int a = *(nums1 + i - 1);
    int b = *(nums2 + j - 1);

    if (a > b) {
      // Drop the second part of nums1 and the first part of nums2
      return _find(nums1, i, nums2 + j, m - j, pos - j);
    } else if (a < b) {
      // Drop the first part of nums1 and the second part of nums2
      return _find(nums1 + i, n - i, nums2, j, pos - i);
    } else {
      return a;
    }
  }

public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    if ((n + m) & 1) { // odd
      return _find(nums1.begin(), n, nums2.begin(), m, (n + m) / 2 + 1);
    }
    return (_find(nums1.begin(), n, nums2.begin(), m, (n + m) / 2)
      + _find(nums1.begin(), n, nums2.begin(), m, (n + m) / 2  + 1)) / 2.0;
  }
};

int main() {
  return 0;
}
