// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     May 25, 2014
//
// Clone Graph
// Clone an undirected graph. Each node in the graph contains a label and a list
// of its neighbors.

#include "leetcode.h"

class Solution {
  typedef UndirectedGraphNode UGN;
  // DFS
  UGN *cloneGraph1(UGN *node) {
    unordered_map<int, UGN *> mp;
    return dfs1(node, mp);
  }

  UGN* dfs1(UGN* node, unordered_map<int, UGN *>& mp) {
    if (!node) {
      return nullptr;
    }
    if (mp.count(node->label)) {
      return mp[node->label];
    }

    UGN* cur = new UGN(node->label);
    mp[cur->label] = cur;
    for (auto it : node->neighbors) {
      cur->neighbors.push_back(dfs1(it, mp));
    }
    return cur;
  }

  // BFS
  UGN* cloneGraph2(UGN* node) {
    if (!node) {
      return nullptr;
    }
    queue<UGN*> que;
    unordered_map<UGN*, UGN*> node_map;

    que.push(node);
    node_map[node] = new UGN(node->label);
    while (que.size()) {
      UGN* cur = que.front();
      que.pop();

      for (auto& neighbor : cur->neighbors) {
        if (! node_map.count(neighbor)) {
          node_map[neighbor] = new UGN(neighbor->label);
          que.push(neighbor);
        }
        node_map[cur]->neighbors.push_back(node_map[neighbor]);
      }
    }
    return node_map[node];
  }

public:
  UGN *cloneGraph(UGN *node) {
    return cloneGraph1(node);
    //return cloneGraph2(node);
  }
};

int main() {
  return 0;
}
