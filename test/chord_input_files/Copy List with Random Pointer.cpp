// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Copy List with Random Pointer
// A linked list is given such that each node contains an additional random 
// pointer which could point to any node in the list or null.
// Return a deep copy of the list.

#include "leetcode.h"

class Solution {
  RandomListNode *copyRandomList1(RandomListNode *head) {
    if (head == nullptr) {
      return nullptr;
    }
    RandomListNode dummy(0), *new_cur = &dummy, *cur = head;
    unordered_map<RandomListNode*, RandomListNode*> mp;

    // new_cur is one step slower than cur
    while (cur) {
      if (mp.count(cur) == 0) {
        mp[cur] = new RandomListNode(cur->label);
      }
      if (cur->random && mp.count(cur->random) == 0) {
        mp[cur->random] = new RandomListNode(cur->random->label);
      }
      new_cur->next = mp[cur];
      new_cur = new_cur->next;
      new_cur->random = mp[cur->random];
      cur = cur->next;
    }

    return dummy.next;
  }

  RandomListNode *copyRandomList2(RandomListNode *head) {
    RandomListNode* cur = head;
    while (cur) {
      RandomListNode* new_node = new RandomListNode(cur->label);
      new_node->next = cur->next;
      cur->next = new_node;
      cur = cur->next->next;
    }

    cur = head;
    while (cur) {
      if (cur->random) {
        cur->next->random = cur->random->next;
      }
      cur = cur->next->next;
    }

    RandomListNode dummy(0), *new_cur = &dummy;
    cur = head;
    while (cur) {
      new_cur->next = cur->next;
      cur->next = cur->next->next;
      new_cur = new_cur->next;

      cur = cur->next;
    }

    return dummy.next;
  }

public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    return copyRandomList1(head);
    //return copyRandomList2(head);
  }
};

int main() {
  return 0;
}
