// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 18, 2014
// Update:     May 18, 2014
//
// Linked List Cycle
//Given a linked list, determine if it has a cycle in it.

#include "leetcode.h"

class Solution {
public:
  bool hasCycle(ListNode *head) {
    // This boundary check is vital to handle the case with only one node
    if (!head || !head->next) {
      return false;
    }

    ListNode* slow = head, *fast = head;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        return true;
      }
    }

    return false;
  }
};

int main() {
  return 0;
}
