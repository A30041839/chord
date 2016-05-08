// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 9, 2014
// Update:     May 6, 2014
//
// Partition List
// Given a linked list and a value x, partition it such that all nodes less than 
// x come before nodes greater than or equal to x.
// You should preserve the original relative order of the nodes in each of the 
// two partitions.
// For example,
// Given 1->4->3->2->5->2 and x = 3,
// return 1->2->2->4->3->5.

#include "leetcode.h"

class Solution {
public:
  ListNode *partition(ListNode *head, int x) {
    if (!head) {
      return nullptr;
    }

    ListNode ldummy(0), *lcur = &ldummy;
    ListNode rdummy(0), *rcur = &rdummy;

    while (head) {
      if (head->val < x) {
        lcur->next = head;
        lcur = lcur->next;
      } else {
        rcur->next = head;
        rcur = rcur->next;
      }
      head = head->next;
    }

    rcur->next = nullptr;
    lcur->next = rdummy.next;
    return ldummy.next;
  }
};

int main() {
  return 0;
}
