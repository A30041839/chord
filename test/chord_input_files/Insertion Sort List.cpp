// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 20, 2014
// Update:     May 20, 2014
//
// Insertion Sort List
// Sort a linked list using insertion sort.

#include "leetcode.h"

using namespace std;

class Solution {
  void insert(ListNode* head, ListNode* cur) {
    while (head->next && head->next->val < cur->val) {
      head = head->next;
    }
    cur->next = head->next;
    head->next = cur;
  }

public:
  ListNode *insertionSortList(ListNode *head) {
    // The dummy node is the empty node. I usually link it to the node head.
    // But here I don't.
    ListNode dummy(0), *cur = head;

    while (cur) {
      // Node next should be preserved since it might be changed in the
      // insertion operation.
      ListNode* next = cur->next;
      insert(&dummy, cur);
      cur = next;
    }

    return dummy.next;
  }
};

int main() {
  return 0;
}
