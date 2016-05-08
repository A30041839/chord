// Author:     ct.Liu, lcntn3@gmail.com
// Date:       May 18, 2014
// Update:     May 18, 2014
//
// Linked List Cycle II 
// Given a linked list, return the node where the cycle begins. If there is no 
// cycle, return null.

#include "leetcode.h"

class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    // This boundary check is vital
    if (!head || !head->next) {
      return nullptr;
    }

    ListNode* slow = head, *fast = head;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        break;
      }
    }

    if (slow != fast) {
      return nullptr;
    }

    // Easy to proof.
    // Suppose:
    // n: the distance from head to cycle begin
    // k: the distance from cycle begin to the meeting node
    // m: the distance from meeting node to the cycle begin
    // then
    // cycle length = m + k
    // 2(n + k) = n + 2k + m => m = n
    ListNode* intersect = head;
    while (intersect != slow) {
      intersect = intersect->next;
      slow = slow->next;
    }

    return intersect;
  }
};

int main() {
  return 0;
}
