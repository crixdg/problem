#pragma once

#include <bits/stdc++.h>

using namespace std;

struct dsu_t {
  vector<int> p, sz;
  Int comps
  explicit DSU(Int n = 0) : p(n), sz(n, 1), comps(n) { iota(p.begin(), p.end(), Int(0)); }
  Int find(Int x) { return p[x] == x ? x : p[x] = find(p[x]); }
  bool unite(Int a, Int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      return false;
    }
    if (sz[a] < sz[b]) {
      swap(a, b);
    }
    p[b] = a;
    sz[a] += sz[b];
    --comps;
    return true;
  }
  bool same(Int a, Int b) { return find(a) == find(b); }
  Int size(Int x) { return sz[find(x)]; }
};
