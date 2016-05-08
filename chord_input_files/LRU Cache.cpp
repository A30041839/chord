// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 28, 2014
// Updat:      May 28, 2014
//
// LRU Cache
// Design and implement a data structure for Least Recently Used (LRU) cache. 
// It should support the following operations: get and set.
//
// get(key) - Get the value (will always be positive) of the key if the key
// exists in the cache, otherwise return -1.
// set(key, value) - Set or insert the value if the key is not already present. 
// When the cache reached its capacity, it should invalidate the least recently 
// used item before inserting a new item.

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class CacheEntry {
public:
  int key;
  int value;
  explicit CacheEntry(int _key, int _value): key(_key), value(_value) {
  }
};

class LRUCache{
public:
  LRUCache(int capacity): m_size(capacity) {
  }

  int get(int key) {
    if (m_cache_map.count(key) == 0) {
      return -1;
    } else {
      m_cache_list.splice(m_cache_list.begin(), m_cache_list, m_cache_map[key]);
      return m_cache_map[key]->value;
    }
  }

  void set(int key, int value) {
    if (m_cache_map.count(key)) {
      m_cache_list.splice(m_cache_list.begin(), m_cache_list, m_cache_map[key]);
      m_cache_map[key]->value = value;
    } else {
      if (m_cache_list.size() == m_size) {
        m_cache_map.erase(m_cache_list.back().key);
        m_cache_list.pop_back();
      }
      m_cache_list.push_front(CacheEntry(key, value));
      m_cache_map[key] = m_cache_list.begin();
    }
  }

private:
  unordered_map<int, list<CacheEntry>::iterator > m_cache_map;
  list<CacheEntry> m_cache_list;
  int m_size;
};

int main() {
  return 0;
}
