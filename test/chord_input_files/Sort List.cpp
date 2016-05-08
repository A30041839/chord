// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Sort List
// Sort a linked list in O(n log n) time using constant space complexity.

#include "leetcode.h"

class Solution {
  void print_list(ListNode* cur) {
    while (cur) {
      cout << cur->val << ' ';
      cur = cur->next;
    }
    cout << endl;
  }

  ListNode* _merge(ListNode* l, ListNode* r) {
    ListNode dummy(0), *cur = &dummy;

    while (l && r) {
      ListNode*& pmin = l->val > r->val ? r : l;
      cur->next = pmin;
      cur = cur->next;
      pmin = pmin->next;
    }
    cur->next = l ? l : r;

    return dummy.next;
  }

  ListNode* _merge_sort(ListNode*& cur, int st, int ed) {
    if (st == ed) {
      ListNode* p = cur;
      cur = cur->next; // *
      p->next = nullptr; // *
      return p;
    }

    int mid = st + (ed - st) / 2;
    ListNode* l = _merge_sort(cur, st, mid);
    ListNode* r = _merge_sort(cur, mid + 1, ed);

    return _merge(l, r);
  }

  ListNode *merge_sort(ListNode *head) {
    if (! head || ! head->next) {
      return head;
    }
    int n = 0;
    ListNode* cur = head;
    while (cur) {
      cur = cur->next;
      ++n;
    }
    return _merge_sort(head, 0, n - 1);
  }

  ListNode* partition(ListNode* head, ListNode*& l, ListNode*& r) {
    ListNode ldummy(0), *lcur = &ldummy;
    ListNode rdummy(0), *rcur = &rdummy;
    ListNode* pivot = head;
    head = head->next;
    pivot->next = nullptr;

    while (head) {
      if (head->val <= pivot->val) {
        lcur->next = head;
        lcur = lcur->next;
      } else {
        rcur->next = head;
        rcur = rcur->next;
      }
      head = head->next;
    }

    lcur->next = nullptr;
    rcur->next = nullptr;
    l = ldummy.next;
    r = rdummy.next;
    return pivot;
  }

  ListNode* quick_sort(ListNode* head) {
    if (!head || !head->next) {
      return head;
    }

    ListNode* l = nullptr, *r = nullptr;
    ListNode* mid = partition(head, l, r);

    l = quick_sort(l);
    r = quick_sort(r);

    if (l) {
      ListNode* tail = l;
      while (tail->next) {
        tail = tail->next;
      }
      mid->next = r;
      tail->next = mid;
      return l;
    } else {
      mid->next = r;
      return mid;
    }
  }

public:
  ListNode *sortList(ListNode *head) {
    // TLE
    //return quick_sort(head);
    return merge_sort(head);
  }
};

int main() {
  ListNode* head = new ListNode(3);
  head->next = new ListNode(5);
  head->next->next = new ListNode(0);
  head->next->next->next = new ListNode(-1);

  Solution sol;
  ListNode* res = sol.sortList(head);
  while (res) {
    cout << res->val << endl;
    res = res->next;
  }

  return 0;
}
