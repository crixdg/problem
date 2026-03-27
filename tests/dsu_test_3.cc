/** https://judge.yosupo.jp/problem/unionfind */
/** verified find, unite, and same operations **/
#include <bits/stdc++.h>

using namespace std;

/** disjoint set union **/
struct dsu_t {
  int comp_sz;
  vector<int> p, sz;

  explicit dsu_t(int n) : comp_sz(n), p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

  /** find root: path halving compression **/
  int find(int x) {
    while (p[x] != x) {
      p[x] = p[p[x]];
      x = p[x];
    }
    return x;
  }

  /** merge: false if already same set **/
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) { return false; }
    if (sz[a] < sz[b]) { swap(a, b); }
    p[b] = a;
    sz[a] += sz[b];
    comp_sz--;
    return true;
  }

  /** check if two elements are in the same set **/
  bool same(int a, int b) { return find(a) == find(b); }

  /** return the size of the set containing x **/
  int size(int x) { return sz[find(x)]; }

  /** return the number of connected components **/
  int components() { return comp_sz; }
};

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) ((void)0)
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  dsu_t dsu(n);
  {
    while (q--) {
      int t, u, v;
      cin >> t >> u >> v;
      if (t == 0) {
        dsu.unite(u, v);
      } else {
        cout << dsu.same(u, v) << '\n';
      }
    }
  }
  return 0;
}
