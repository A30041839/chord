// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 3, 2014
// Update:     May 3, 2014
//
// Reverse Linked List II
// Reverse a linked list from position m to n. Do it in-place and in one-pass.
// For example:
// Given 1->2->3->4->5->NULL, m = 2 and n = 4,
// return 1->4->3->2->5->NULL.
//
// Note:
// Given m, n satisfy the following condition:
// 1 <= m <= n <= length of list.

#include "leetcode.h"

class Solution {
  ListNode *reverseBetween1(ListNode *head, int m, int n) {
    if (m == n) {
      return head;
    }
    ListNode* p = head, *beforeHead = NULL;
    ListNode* pre = NULL, *cur = NULL;
    int k = 0;

    while (p) {
      cur = p;
      p = p->next;

      if (k == m - 2) {
        beforeHead = cur;
      }
      if (k >= m && k < n && cur) {
        cur->next = pre;
      }
      pre = cur;
      if (k == n - 1) {
        break;
      }

      ++k;
    }

    // Only two conditions:
    // 1) the reverse range does not include the head of the list
    if (m > 1) {
      beforeHead->next->next = p;
      beforeHead->next = pre;
      return head;
    }
    // 2) the reverse range includes the head of the list
    head->next = p;
    return pre;
  }

  // !
  ListNode *reverseBetween2(ListNode *head, int m, int n) {
    if (m >= n) {
      return head;
    }

    ListNode dummy(0), *ins = &dummy;
    dummy.next = head;

    // Move ins to the m - 1 position
    for (int i = 0; i < m - 1; ++i) { // !
      ins = ins->next;
    }

    ListNode* cur = ins->next;
    for (int i = 0; i < n - m; ++i) {
      ListNode* move = cur->next;
      cur->next = move->next;
      move->next = ins->next; // ins->next cannot be replaced by cur
      ins->next = move;
    }

    return dummy.next;
  }

public:
  ListNode *reverseBetween(ListNode *head, int m, int n) {
    //return reverseBetween1(head, m, n);
    return reverseBetween2(head, m, n);
  }
};

int main() {
  int a[] = {1, 2, 3};
  ListNode* head = convert_to_list(a, sizeof(a) / sizeof(a[0]));
  Solution sol;
  ListNode* res = sol.reverseBetween(head, 2, 3);
  print_list(res);
  return 0;
}
