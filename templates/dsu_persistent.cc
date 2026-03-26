#include <bits/stdc++.h>

using namespace std;

/**
 * Rollback DSU: no path compression. unite pushes a change; rollback() undoes
 * last unite. Useful with divide-and-conquer / offline segment trees.
 **/
struct DsuRollback {
  int n, comps;
  vector<int> p, sz;
  struct Change {
    int a, b, sz_a;
  };
  vector<Change> st;
  explicit DsuRollback(int n_ = 0) : n(n_), comps(n_), p(n_), sz(n_, 1) {
    iota(p.begin(), p.end(), 0);
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
