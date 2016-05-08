// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 5, 2014
// Update:     May 5, 2014
//
// Add Two Numbers
// You are given two linked lists representing two non-negative numbers. 
// The digits are stored in reverse order and each of their nodes contain a
// single digit.
// Add the two numbers and return it as a linked list.

#include "leetcode.h"

using namespace std;

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode dummy(0), *cur = &dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
      int sum = carry;
      if (l1) {
        sum += l1->val;
        l1 = l1->next;
      }
      if (l2) {
        sum += l2->val;
        l2 = l2->next;
      }
      cur->next = new ListNode(sum % 10);
      cur = cur->next;
      carry = sum / 10;
    }

    return dummy.next;
  }
};

int main() {
  return 0;
}
