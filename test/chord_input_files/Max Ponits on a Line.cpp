// Author:     ct.Liu, lcndn3@gmail.com
// Date:       May 25, 2014
// Update:     Jul 12, 2014
//
// Max Points on a Line
// Given n points on a 2D plane, find the maximum number of points that lie on
// the same straight line.

#include "leetcode.h"

const double EPS = 1e-5;

class Slope {
public:
  double val;

  explicit Slope(double val): val(val) {
  }

  bool operator==(const Slope& o) const {
    return abs(val - o.val) < EPS;
  }
};

class Hasher {
public:
  size_t operator()(const Slope& o) const {
    return o.val;
  }
};

class Solution {
  int gcd(int a, int b) {
    while (b) {
      int ta = a;
      a = b;
      b = ta % b;
    }
    return a;
  }

  pair<int, int> get_slope1(const Point& a, const Point& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int com_div = gcd(dx, dy);
    if (com_div) {
      dx /= com_div;
      dy /= com_div;
    }
    return {dx, dy};
  }

  int maxPoints1(vector<Point>& points) {
    int n = points.size();
    // unordered_map<pair<int, int>, int> mp
    // is worong, see
    // http://stackoverflow.com/questions/4870437/pairint-int-pair-as-key-of-unordered-map-issue
    map<pair<int, int>, int> mp;
    int res = 0;

    for (int i = 0; i < n; ++i) {
      int same = 0, mx = 0;
      mp.clear();
      for (int j = i; j < n; ++j) {
        if (points[i].x == points[j].x && points[i].y == points[j].y) {
          ++same;
        } else {
          auto slope = get_slope1(points[i], points[j]);
          mx = max(mx, ++mp[slope]);
        }
      }
      res = max(res, same + mx);
    }

    return res;
  }

  int maxPoints2(vector<Point>& points) {
    if (points.size() < 2) {
      return points.size();
    }
    int n = points.size();
    int res = 0;
    //unordered_map<double, int> slope_map;
    unordered_map<Slope, int, Hasher> slope_map;

    for (int i = 0; i < n; ++i) {
      slope_map.clear();
      int same_point = 0, same_line = 0, vertical = 0;
      for (int j = 0; j < n; ++j) {
        if (points[i].x == points[j].x) {
          if (points[i].y == points[j].y) {
            ++same_point;
          } else {
            ++vertical;
          }
        } else {
          Slope slope((points[i].y - points[j].y) * 1.0 / (points[i].x - points[j].x));
          //double slope((points[i].y - points[j].y) * 1.0 / (points[i].x - points[j].x));
          same_line = max(same_line, ++slope_map[slope]);
        }
      }
      res = max(res, max(same_line, vertical) + same_point);
    }

    return res;
  }

public:
  int maxPoints(vector<Point> &points) {
    return maxPoints1(points);
    return maxPoints2(points);
  }
};

int main() {
  return 0;
}
