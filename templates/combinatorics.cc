/**
 *    author: crixdg
 *    timestamp: 28.03.2026 06:25:36
 **/

#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- COMBINATORICS (SMALL VALUES) ----------------------------- **/

struct combinatorics_small_t {
  int sz{0};
  vector<vector<long long>> c{1, vector<long long>(1, 1)};

  combinatorics_small_t() {}
  combinatorics_small_t(int n) { extend(n); }

  void extend(int n) {
    assert(n >= 0 && n <= 2000);
    if (n <= sz) { return; }
    c.resize(n + 1, vector<long long>(n + 1));
    for (int i = sz + 1; i <= n; i++) { c[i][0] = c[i][i] = 1; }
    for (int i = sz + 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
      }
    }
    sz = n;
  }

  long long C(int n, int k) {
    if (k < 0 || k > n) { return 0; }
    extend(n);
    return c[n][k];
  }
};

using comb_t = combinatorics_small_t;
