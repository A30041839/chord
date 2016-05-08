// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 4, 2014
// Update:     May 4, 2014
//
// Swap Nodes in Pairs
// Given a linked list, swap every two adjacent nodes and return its head.
// For example,
// Given 1->2->3->4, you should return the list as 2->1->4->3.
// Your algorithm should use only constant space. You may not modify the values
// in the list, only nodes itself can be changed.

#include "leetcode.h"

class Solution {
  // Dummy + iterative solution
  ListNode *swapPairs1(ListNode* head) {
    ListNode dummy(0), *cur = &dummy;
    dummy.next = head;

    while (cur->next && cur->next->next) {
      ListNode* move = cur->next->next;
      cur->next->next = move->next;
      move->next = cur->next;
      cur->next = move;
      cur = move->next;
    }

    return dummy.next;
  }

  // Recursive solution
  ListNode *swapPairs2(ListNode* head) {
    if (! head || ! head->next) {
      return head;
    }

    ListNode* fst = head, *snd = head->next;
    fst->next = snd->next;
    snd->next = fst;
    fst->next = swapPairs(fst->next);

    return snd;
  }

public:
  ListNode *swapPairs(ListNode* head) {
    //return swapPairs1(head);
    return swapPairs2(head);
  }
};

int main() {
  return 0;
}
