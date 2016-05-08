// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 24, 2014
// Update:     May 24, 2014
//
// Gas Station
// There are N gas stations along a circular route, where the amount of gas at 
// station i is gas[i].
// You have a car with an unlimited gas tank and it costs cost[i] of gas to 
// travel from station i to its next station (i+1). You begin the journey with 
// an empty tank at one of the gas stations.
//
// Return the starting gas station's index if you can travel around the circuit
// once, otherwise return -1.
//
// Note:
// The solution is guaranteed to be unique.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();
    for (int i = 0; i < n;) {
      int tank = 0, count = 0, j = i;
      while (count++ < n) {
        tank += gas[(j + n) % n] - cost[(j + n) % n];
        ++j;
        if (tank < 0) {
          break;
        }
      }
      if (tank >= 0) {
        return i;
      }
      i = j;
    }

    return -1;
  }

  int canCompleteCircuit2(vector<int>& gas, vector<int>& cost) {
    assert(gas.size() == cost.size());
    int n = gas.size();
    int left = 0, sum = 0;
    int idx = 0;

    for (int i = 0; i < n; ++i) {
      int diff = gas[i] - cost[i];
      left += diff;
      sum += diff;
      if (sum < 0) {
        sum = 0;
        idx = i;
      }
    }

    return left < 0 ? -1 : (idx + 1) % n;
  }

public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    //return canCompleteCircuit1(gas, cost);
    return canCompleteCircuit2(gas, cost);
  }
};

int main() {
  vector<int> gas = {1, 4};
  vector<int> cost = {3, 1};

  Solution sol;
  int res = sol.canCompleteCircuit(gas,cost);
  cout << res << endl;

  return 0;
}
