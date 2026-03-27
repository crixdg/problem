/** https://judge.yosupo.jp/problem/persistent_unionfind **/
#include <bits/stdc++.h>

using namespace std;
// ----------------------------- DSU ROLLBACK -----------------------------

struct dsu_rollback_t {
  int comps;
  vector<int> p, sz;
  struct change_t {
    int a, b, sz_a;
  };
  vector<change_t> history;

  explicit dsu_rollback_t(int n) : comps(n), p(n), sz(n, 1) {
    iota(p.begin(), p.end(), 0);
  }

  /** find root; no path compression, requires for safe rollback **/
  int find(int x) {
    while (p[x] != x) { x = p[x]; }
    return x;
  }

  /** merge; false if already same set **/
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) { return false; }
    if (sz[a] < sz[b]) { std::swap(a, b); }
    history.emplace_back(a, b, sz[a]);
    p[b] = a;
    sz[a] += sz[b];
    comps--;
    return true;
  }

  /** rollback last merge **/
  void rollback() {
    if (history.empty()) { return; }
    change_t c = history.back();
    history.pop_back();
    p[c.b] = c.b;
    sz[c.a] = c.sz_a;
    comps++;
  }

  /** rollback to a checkpoint **/
  void rollback(int checkpoint) {
    while ((int)history.size() > checkpoint) { rollback(); }
  }

  /** return the number of saved merges **/
  int save() { return history.size(); }

  /** check if two elements are in the same set **/
  bool same(int a, int b) { return find(a) == find(b); }

  /** return the size of the set containing x **/
  int size(int x) { return sz[find(x)]; }

  /** return the number of connected components **/
  int components() { return comps; }
};

// ----------------------------- MAIN -----------------------------

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
  vector<vector<int>> qs(q);
  vector<vector<int>> g(q);
  for (int i = 0; i < q; i++) {
    int op, k, u, v;
    cin >> op >> k >> u >> v;
    if (k >= 0) {
      g[k].push_back(i);
    }
    qs[i] = {op, k, u, v};
  }

  dsu_rollback_t dsu(n);
  {
    vector<bool> vs(q);
    function<void(int)> dfs = [&](int u) {
      int now = dsu.save();
      if (qs[u][0] == 0) {
        dsu.unite(qs[u][2], qs[u][3]);
      } else {
        qs[u].push_back(dsu.same(qs[u][2], qs[u][3]));
      }
      for (int v : g[u]) {
        if (!vs[v]) {
          vs[v] = true;
          dfs(v);
        }
      }
      dsu.rollback(now);
    };

    for (int i = 0; i < q; i++) {
      if (!vs[i]) {
        vs[i] = true;
        dfs(i);
      }
    }

    for (int i = 0; i < q; i++) {
      if (qs[i].size() == 5) { cout << qs[i][4] << '\n'; }
    }
  }
  return 0;
}
