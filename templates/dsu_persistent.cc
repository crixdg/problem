/**
 *    author: crixdg
 *    timestamp: 27.03.2026 02:54:43
 **/

#include <bits/stdc++.h>

using namespace std;

struct persistent_dsu_t {
  int comps;
  vector<int> p, sz;
  struct change_t {
    int a, b, sz_a;
  };
  vector<change_t> history;

  explicit persistent_dsu_t(int n) : comps(n), p(n), sz(n, 1) {
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
