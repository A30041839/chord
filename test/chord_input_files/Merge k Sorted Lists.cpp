// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 10, 2014
// Update:     May 10, 2014
//
// Merge k Sorted Lists
// Merge k sorted linked lists and return it as one sorted list. Analyze and
// describe its complexity.

#include "leetcode.h"

class Solution {
public:
  ListNode *mergeKLists(vector<ListNode*>& lists) {
    ListNode dummy(0), *cur = &dummy;

    auto cmp = [](const ListNode * p, const ListNode * q) {
      return p->val > q->val;
    };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

    for (auto& lst : lists) {
      if (lst) {
        pq.push(lst);
      }
    }

    while (!pq.empty()) {
      ListNode* top = pq.top();
      pq.pop();
      cur->next = top;
      cur = cur->next;

      if (top->next) {
        pq.push(top->next);
      }
    }

    return dummy.next;
  }
};

int main() {
  return 0;
}
