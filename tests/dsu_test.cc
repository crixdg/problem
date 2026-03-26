#include <bits/stdc++.h>

using namespace std;
/** problems:
 *    - test dsu + size of set containing x: https://codeforces.com/problemset/problem/1167/C
 **/

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

int main() {
  int n, m;
  cin >> n >> m;
  dsu_t dsu(n);
  {
    while (m--) {
      int k;
      cin >> k;
      if (k == 0) {
        continue;
      }
      int x;
      cin >> x;
      while (--k) {
        int y;
        cin >> y;
        dsu.unite(x - 1, y - 1);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << dsu.size(i) << ' ';
  }
  cout << '\n';
  return 0;
}
