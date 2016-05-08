// Author:     ct.Liu, lcntn3@gmail.com
// Date:       Apr 30, 2014
// Update:     Ari 30, 2014
//
// Remove Duplicates from Sorted List II
// Given a sorted linked list, delete all nodes that have duplicate numbers,
// leaving only distinct numbers from the original list.
// For example,
// Given 1->2->3->3->4->4->5, return 1->2->5.
// Given 1->1->1->2->3, return 2->3.

#include "leetcode.h"

class Solution {
  // Iterative solution
  ListNode *deleteDuplicates1(ListNode *head) {
    ListNode dummy(0), *cur = &dummy; // dummpy->val = 0?
    dummy.next = head;

    while (cur && cur->next) {
      ListNode* p = cur->next;
      int val = p->val;

      // There are no duplicated elements
      // node `cur` is needed in the list, check the next two nodes followed
      // by `cur`
      if (!p->next || p->next->val != val) {
        cur = cur->next;
        continue;
      }

      // There exist duplicated elements
      while (p && p->val == val) {
        ListNode* del = p;
        p = p->next;
        delete del;
      }
      cur->next = p;
    }

    return dummy.next;
  }

  // Recursive solution
  ListNode *deleteDuplicates2(ListNode *head) {
    if (head == nullptr) {
      return nullptr;
    }
    if (head->next == nullptr || head->next->val != head->val) {
      head->next = deleteDuplicates2(head->next);
      return head;
    }

    int val = head->val;
    while (head && val == head->val) {
      ListNode* del = head;
      head = head->next;
      delete del;
    }
    return deleteDuplicates2(head);
  }

public:
  ListNode *deleteDuplicates(ListNode *head) {
    //return deleteDuplicates1(head);
    return deleteDuplicates2(head);
  }
};

int main() {
  return 0;
}
