// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 13, 2014
// Update:     May 13, 2014
//
// Pascal's Triangle
// Given numRows, generate the first numRows of Pascal's triangle.
// For example, given numRows = 5,
// Return
// [
//      [1],
//     [1,1],
//    [1,2,1],
//   [1,3,3,1],
//  [1,4,6,4,1]
// ]

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int> > generate(int numRows) {
    vector<vector<int>> res(numRows);

    for (int i = 0; i < numRows; ++i) {
      res[i].assign(i + 1, 1);
      for (int j = 1; j < i; ++j) {
        res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
      }
    }

    return res;
  }
};

int main() {
  return 0;
}
