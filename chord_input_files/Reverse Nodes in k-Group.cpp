// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Reverse Nodes in k-Group
// Given a linked list, reverse the nodes of a linked list k at a time and
// return its modified list.
// 
// If the number of nodes is not a multiple of k then left-out nodes in the end 
// should remain as it is.
// 
// You may not alter the values in the nodes, only nodes itself may be changed.
// Only constant memory is allowed.

#include "leetcode.h"

class Solution {

   ListNode* _reverse(ListNode* head, int k) {
    ListNode* cur = head->next;

    for (int i = 0; i < k - 1; ++i) {
      ListNode* move = cur->next;
      cur->next = move->next;
      move->next = head->next;
      head->next = move;
    }

    return cur;
  }

public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (! head || k <= 1) {
      return head;
    }
    ListNode dummy(0), *cur = &dummy;
    dummy.next = head;
    int len = 0;

    while (head) {
      head = head->next;
      ++len;
    }

    int m = len / k;
    while (m--) {
      cur = _reverse(cur, k);
    }

    return dummy.next;
  }
};

int main() {
  int a[] = {1, 2, 3, 4};
  ListNode* head = convert_to_list(a, sizeof(a) / sizeof(a[0]));

  Solution sol;
  ListNode* res = sol.reverseKGroup(head, 2);
  print_list(res);

  return 0;
}
