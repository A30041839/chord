// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 3, 2014
// Update:     May 3, 2014
//
// Rotate List
// Given a list, rotate the list to the right by k places, where k is non-negative.
// For example:
// Given 1->2->3->4->5->NULL and k = 2,
// return 4->5->1->2->3->NULL.

#include "leetcode.h"

class Solution {
  ListNode *rotateRight1(ListNode* head, int k) {
    if (!head || k == 0) {
      return head;
    }

    int n = 1;
    ListNode* tail = head;
    while (tail->next) {
      ++n;
      tail = tail->next;
    }
    k %= n;
    if (!k) {
      return head;
    }

    ListNode* cur = head;
    for (int i = 0; i < n - k - 1; ++i) {
      cur = cur->next;
    }
    tail->next = head;
    head = cur->next;
    cur->next = nullptr;

    return head;
  }

public:
  ListNode *rotateRight(ListNode *head, int k) {
    return rotateRight1(head, k);
  }
};

int main() {
  int a[] = {1, 2};
  ListNode* head = convert_to_list(a, sizeof(a) / sizeof(a[0]));

  Solution sol;
  sol.rotateRight(head, 3);
  return 0;
}
