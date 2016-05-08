// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 6, 2014
// Update:     May 6, 2014
//
// Merge Two Sorted Lists
// Merge two sorted linked lists and return it as a new list.
// The new list should be made by splicing together the nodes of the first two lists.

#include "leetcode.h"

class Solution {
  ListNode *mergeTwoLists1(ListNode *l1, ListNode *l2) {
    ListNode dummy(0), *cur = &dummy;

    while (l1 && l2) {
      ListNode*& p_min = l1->val < l2->val ? l1 : l2;
      cur->next = p_min;
      p_min = p_min->next;
      cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;

    return dummy.next;
  }

public:
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    return mergeTwoLists1(l1, l2);
  }
};

int main() {
  return 0;
}
