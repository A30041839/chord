// Author:     ct.Liu, lcndn3@gmail.com
// Date:       Apr 30, 2014
// Update:     Ari 30, 2014
//
// Remove Duplicates from Sorted List
// Given a sorted linked list, delete all duplicates such that each element appear only once.
//
// For example,
// Given 1->1->2, return 1->2.
// Given 1->1->2->3->3, return 1->2->3.

#include "leetcode.h"

class Solution {
  ListNode *deleteDuplicates1(ListNode *head) {
    ListNode* p = head;

    while (p) {
      ListNode* cur = p;
      while (cur && cur->val == p->val) {
        cur = cur->next;
      }
      p->next = cur;
      // Here, p->next is the same with cur.
      p = p->next;
    }

    return head;
  }

  // !
  ListNode *deleteDuplicates2(ListNode *head) {
    if (!head || !head->next) {
      return head;
    }

    ListNode* cur = head;
    while (cur->next) {
      ListNode* p = cur->next;
      if (cur->val == p->val) { // !!
        cur->next = p->next;
        delete p; // since the element has been ignored, so deletes it.
      } else {
        cur = cur->next;
      }
    }

    return head;
  }

  // !
  ListNode *deleteDuplicates3(ListNode *head) {
    if (head == nullptr) {
      return nullptr;
    }

    if (head->next != nullptr) {
      if (head->next->val == head->val) {
        head->next = head->next->next;
        head = deleteDuplicates3(head);
      } else {
        head->next = deleteDuplicates3(head->next);
      }
    }
    return head;
  }

public:
  ListNode *deleteDuplicates(ListNode *head) {
    //return deleteDuplicates1(head);
    return deleteDuplicates2(head);
    //return deleteDuplicates3(head);
  }
};

int main() {
  return 0;
}
