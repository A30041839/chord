// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Reorder List
// Given a singly linked list L: L0→L1→…→Ln-1→Ln,
// reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
// You must do this in-place without altering the nodes' values.
//
// For example,
// Given {1,2,3,4}, reorder it to {1,4,2,3}.

#include "leetcode.h"

class Solution {
public:
  //void reorderList(ListNode* head) {
    //if (!head || !head->next) {
      //return ;
    //}

    //ListNode* slow = head, *fast = head;
    //while (fast && fast->next && fast->next->next) {
      //slow = slow->next;
      //fast = fast->next->next;
    //}
    //ListNode* tail = slow;

    //ListNode* cur = tail->next;
    //while (cur && cur->next) {
      //ListNode* move = cur->next;
      //cur->next = move->next;
      //move->next = tail->next;
      //tail->next = move;
    //}

    //cur = head;
    //while (cur != tail && tail->next) {
      //ListNode* move = tail->next;
      //tail->next = move->next;
      //move->next = cur->next;
      //cur->next = move;
      //cur = cur->next->next;
    //}
  //}


  void reorderList(ListNode *head) {
    if (!head || !head->next) {
      return ;
    }

    /*
    // Find the middle node
    ListNode* slow = head, *fast = head->next->next;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    if (fast) { // when there are odd nodes
      slow = slow->next;
    }
    */
    ListNode* slow = head, *fast = head;
    while (fast && fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;
    }


    // Reverse the latter half of the linked list
    ListNode* mid = slow, *cur = mid->next;
    while (cur->next) {
      ListNode* move = cur->next;
      cur->next = move->next;
      move->next = mid->next;
      mid->next = move;
    }

    // Reconnect
    cur = head;
    while (cur != mid && mid->next) {
      ListNode* move = mid->next;
      mid->next = move->next;
      move->next = cur->next;
      cur->next = move;
      cur = cur->next->next; // !!
    }
  }
};

int main() {
  Solution sol;
  int vec[] = {1, 2, 3, 4};
  ListNode* head = convert_to_list(vec, 4);

  sol.reorderList(head);
  print_list(head);
  return 0;
}
