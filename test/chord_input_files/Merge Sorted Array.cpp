// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 6, 2014
// Update:     May 6, 2014
//
// Merge Sorted Array
// Given two sorted integer arrays A and B, merge B into A as one sorted array.
//
// Note:
// You may assume that A has enough space to hold additional elements from B. 
// The number of elements initialized in A and B are m and n respectively.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
      nums1[k--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
    }
    while (j >= 0) {
      nums1[k--] = nums2[j--];
    }
    // No need to check array A[i], since both A[] and B[] are sorted, if i >= 0,
    // then A[0...i] is still sorted and smaller then any element in B[]
  }
};

int main() {
  return 0;
}
