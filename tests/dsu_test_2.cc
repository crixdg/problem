/** https://codeforces.com/problemset/problem/722/C **/
/** verified find, unite, and extended merge operation **/
#include <bits/stdc++.h>

using namespace std;

/** disjoint set union **/
struct dsu_t {
  int comp_sz;
  vector<int> p, sz;

  dsu_t(int n) : comp_sz(n), p(n), sz(n, 1) {
    iota(p.begin(), p.end(), 0);
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
  int n;
  cin >> n;
  vector<long long> as(n);
  for (long long &d : as) {
    cin >> d;
  }
  vector<int> ds(n);
  for (int &d : ds) {
    cin >> d;
  }
  vector<long long> anss(n);
  {
    vector<bool> vs(n);
    dsu_t dsu(n);

    auto merge = [&](int a, int b) {
      int u = dsu.find(a);
      int v = dsu.find(b);
      if (dsu.unite(u, v)) {
        int root = dsu.find(a);
        as[root] = as[u] + as[v];
      }
    };

    for (int i = n - 1; i >= 0; i--) {
      int d = ds[i] - 1;
      vs[d] = true;
      if (d > 0 && vs[d - 1]) { merge(d, d - 1); }
      if (d < n - 1 && vs[d + 1]) { merge(d, d + 1); }
      if (i > 0) { anss[i - 1] = max(anss[i], as[dsu.find(d)]); }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << anss[i] << '\n';
  }
  return 0;
}
