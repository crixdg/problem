#include<bits/stdc++.h>

struct combinatorics_t {
  using ll = long long;

  int n;
  std::vector<int> fact, ifact;
  combinatorics_t(int n) : fact(n + 1), ifact(n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
      fact[i] = fact[i - 1] * i;
    }
  }

  ll C(int n, int k, int m = MOD) {}
};
