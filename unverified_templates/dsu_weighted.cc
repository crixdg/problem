/**
 *    author: crixdg
 *    timestamp: 27.03.2026 02:42:48
 **/

#include <bits/stdc++.h>

using namespace std;

/** weighted disjoint set union **/
struct weighted_dsu_t {
  int comp_sz;
  vector<int> p, sz;
  vector<long long> w;

  explicit weighted_dsu_t(int n) : comp_sz(n), p(n), w(n, 0), sz(n, 1) {
    iota(p.begin(), p.end(), 0);
  }

  /** find root; full path compression **/
  std::pair<int, long long> find(int x) {
    if (p[x] == x) { return {x, 0}; }
    auto [r, dw] = find(p[x]);
    return {p[x] = r, w[x] += dw};
  }

  /** merge; false if not possible to link with given weight **/
  bool unite(int x, int y, long long d) {
    auto [fx, wx] = find(x);
    auto [fy, wy] = find(y);
    if (fx == fy) { return wx - wy == d; }
    if (sz[fx] < sz[fy]) {
      swap(fx, fy);
      swap(wx, wy);
      d = -d;
    }
    // p[fy] = fx => label(fx) = label(fy) + w[fy]
    // label(x) - label(y) = d after linking
    // label(fx) + wx - label(fy) - wy = d
    // label(fx) + wx - (label(fx) + w[fy]) - wy = d
    // wx - w[fy] - wy = d
    // => w[fy] = wx - wy - d
    p[fy] = fx;
    w[fy] = wx - wy - d;
    sz[fx] += sz[fy];
    comp_sz--;
    return true;
  }

  /** check if two elements are in the same set **/
  bool same(int x, int y) { return find(x).first == find(y).first; }

  /** return the weight of the set containing x **/
  long long weight(int x) { return find(x).second; }

  /** return the size of the set containing x **/
  int size(int x) { return sz[find(x).first]; }

  /** return the number of connected components **/
  int components() { return comp_sz; }
};
