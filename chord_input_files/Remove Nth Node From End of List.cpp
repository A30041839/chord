// Author:     ct.Liu, lcndn3@gmail.com
// Date:       Apr 30, 2014
// Update:     Apr 30, 2014
//
// Remove Nth Node From End of List
// Given a linked list, remove the nth node from the end of list and return its head.
// For example,
// Given linked list: 1->2->3->4->5, and n = 2.
// After removing the second node from the end, the linked list becomes 1->2->3->5.
//
// Note:
// Given n will always be valid.
// Try to do this in one pass.

#include "leetcode.h"

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode dummy(0), *fast = &dummy, *slow = &dummy;
    dummy.next = head;

    while (n--) {
      fast = fast->next;
    }
    while (fast->next) {
      fast = fast->next;
      slow = slow->next;
    }
    ListNode* del = slow->next;
    slow->next = del->next;
    delete del;

    return dummy.next;
  }
};

int main() {
  return 0;
}
