#include <bits/stdc++.h>

struct dsu_t {
  int n, comps;
  std::vector<int> p, sz;

  dsu_t(int n_ = 0) : n(n_), comps(n_), p(n_), sz(n_, 1) {
    std::iota(p.begin(), p.end(), 0);
  }

  /** find root; path halving compression **/
  int find(int x) {
    while (p[x] != x) {
      p[x] = p[p[x]];
      x = p[x];
    }
    return x;
  }

  /** merge; false if already same set **/
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) { return false; }
    if (sz[a] < sz[b]) { std::swap(a, b); }
    p[b] = a;
    sz[a] += sz[b];
    comps--;
    return true;
  }

  /** check if two elements are in the same set **/
  bool same(int a, int b) { return find(a) == find(b); }

  /** return the size of the set containing x **/
  int size(int x) { return sz[find(x)]; }
};

/**
 * Weighted DSU: maintain x - y = d when merging components.
 * Internally: w[x] = "label(x) - label(parent[x])"; find returns root and
 * label(x) - label(root). unite(x, y, d): enforce label(x) - label(y) = d.
 * Returns false if contradicts existing constraints (same root, wrong diff).
 **/
class weighted_dsu_t {
  int n;
  std::vector<int> p, sz;
  std::vector<long long> w;

  weighted_dsu_t(int n_ = 0) : n(n_), p(n_), w(n_, 0), sz(n_, 1) {
    std::iota(p.begin(), p.end(), 0);
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
      std::swap(fx, fy);
      std::swap(wx, wy);
      d = -d;
    }
    // p[fy]=fx, w[fy]=wx-wy-d  <=>  label(x)-label(y)=d after linking
    p[fy] = fx;
    w[fy] = wx - wy - d;
    sz[fx] += sz[fy];
    return true;
  }
  bool same(int x, int y) { return find(x).first == find(y).first; }
};

/**
 * Rollback DSU: no path compression. unite pushes a change; rollback() undoes
 * last unite. Useful with divide-and-conquer / offline segment trees.
 **/
struct DsuRollback {
  int n, comps;
  std::vector<int> p, sz;
  struct Change {
    int a, b, sz_a;
  };
  std::vector<Change> st;
  explicit DsuRollback(int n_ = 0) : n(n_), comps(n_), p(n_), sz(n_, 1) {
    std::iota(p.begin(), p.end(), 0);
  }
  int find(int x) {
    while (p[x] != x) { x = p[x]; }
    return x;
  }
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) { return false; }
    if (sz[a] < sz[b]) { std::swap(a, b); }
    st.push_back({a, b, sz[a]});
    p[b] = a;
    sz[a] += sz[b];
    comps--;
    return true;
  }
  void rollback() {
    assert(!st.empty());
    Change c = st.back();
    st.pop_back();
    p[c.b] = c.b;
    sz[c.a] = c.sz_a;
    comps++;
  }
  bool same(int a, int b) { return find(a) == find(b); }
};
