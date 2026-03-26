#include <bits/stdc++.h>

using namespace std;

/** weighted disjoint set union **/
class weighted_dsu_t {
  int n;
  vector<int> p, sz;
  vector<long long> w;

  weighted_dsu_t(int n_ = 0) : n(n_), p(n_), w(n_, 0), sz(n_, 1) {
    iota(p.begin(), p.end(), 0);
  }

  std::pair<int, long long> find(int x) {
    if (p[x] == x) { return {x, 0}; }
    auto [r, dw] = find(p[x]);
    w[x] += dw;
    p[x] = r;
    return {p[x], w[x]};
  }

  bool unite(int x, int y, long long d) {
    auto [fx, wx] = find(x);
    auto [fy, wy] = find(y);
    if (fx == fy) { return wx - wy == d; }
    if (sz[fx] < sz[fy]) {
      swap(fx, fy);
      swap(wx, wy);
      d = -d;
    }
    // p[fy] = fx, w[fy] = wx-wy-d  <=>  label(x)-label(y)=d after linking
    p[fy] = fx;
    w[fy] = wx - wy - d;
    sz[fx] += sz[fy];
    return true;
  }
  bool same(int x, int y) { return find(x).first == find(y).first; }
};
// clang-format on
