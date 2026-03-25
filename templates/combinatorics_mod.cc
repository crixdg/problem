/**
 *    author: crixdg
 *    modified: 25.03.2026 12:08:30
 *    created: 25.03.2026 12:08:30
 **/
#include <bits/stdc++.h>
#include "modular.cc"

// --------------------- COMBINATORICS --------------------------

/** combinatorics class for prime modulus **/
// clang-format off
template <integer_c T, T *M_>
class combinatorics_prime_t {
public:
  using M = modular_t<T, M_>;
  combinatorics_prime_t() { build(0); }
  combinatorics_prime_t(int n) { build(n); }

  void build(int n) {
    n = std::max(n, n_);
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = ifact[0] = 1;
    if (n <= n_) { return; }
    for (int i = n_ + 1; i <= n; i++) {
      fact[i] = fact[i - 1] * i;
    }
    ifact[n] = inverse(fact[n], *M_);
    assert(ifact[n] != M(-1));
    for (int i = n - 1; i > n_; i--) {
      ifact[i] = ifact[i + 1] * (i + 1);
    }
    n_ = n;
  }

  M C(int n, int k) {
    if (k < 0 || k > n) { return 0; }
    build(n); return fact[n] * ifact[k] * ifact[n - k];
  }

  M P(int n, int k) {
    if (k < 0 || k > n) { return 0; }
    build(n); return fact[n] * ifact[n - k];
  }

private:
  int n_; std::vector<M> fact, ifact;
};

using comb_pr_t= combinatorics_prime_t<mod_t, &md>;
// clang-format on

/** combinatorics class for general modulus **/
// clang-format off
template <integer_c T, T *M_>
class combinatorics_general_t {
  public:
  using M = modular_t<T, M_>;
  private:
    int n_;
    std::vector<M> fact, ifact;
};
// clang-format on
