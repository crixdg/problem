/**
 *    author: crixdg
 *    modified: 25.03.2026 15:34:46
 *    created: 25.03.2026 12:08:30
 **/
#include "modular.cc"
#include <bits/stdc++.h>

// --------------------- COMBINATORICS --------------------------

/** combinatorics class for prime modulus **/
/** requires M_ to be a prime number **/
template <integer_c T, T *M_, int MAX_N_>
class combinatorics_prime_t {
public:
  using ll = long long;
  using _Mt = modular_t<T, M_>;
  combinatorics_prime_t() : n_(0), fact_(1, _Mt(1)), ifact_(1, _Mt(1)) {}
  combinatorics_prime_t(int n) : n_(0), fact_(1, _Mt(1)), ifact_(1, _Mt(1)) { extend(n); }

  void extend(ll n) {
    n = static_cast<int>(std::min(n, std::min<ll>(*M_ - 1, MAX_N_)));
    if (n <= n_) { return; }
    fact_.resize(n + 1), ifact_.resize(n + 1);
    for (int i = n_ + 1; i <= n; i++) {
      fact_[i] = fact_[i - 1] * i;
    }
    ifact_[n] = inverse(fact_[n], *M_);
    for (int i = n - 1; i > n_; i--) {
      ifact_[i] = ifact_[i + 1] * (i + 1);
    }
    n_ = n;
  }

  _Mt C(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    extend(n);
    if (n <= n_) { return fact_[n] * ifact_[k] * ifact_[n - k]; }
    return C(n % *M_, k % *M_) * C(n / *M_, k / *M_);
  }

  _Mt P(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    extend(n);
    if (n <= n_) { return fact_[n] * ifact_[n - k]; }
    if (k >= *M_) { return _Mt(0); }
    assert(k <= n_);
    return C(n, k) * fact_[k];
  }

private:
  int n_;
  std::vector<_Mt> fact_, ifact_;
};

using comb_pr_t = combinatorics_prime_t<mod_t, &md, int(2e7)>;
// clang-format on

/** combinatorics class for prime^k modulus **/
/** requires M_ to be a prime^k number **/
template <integer_c T, T *M_, int MAX_N_>
class combinatorics_prime_power_t {
public:
  using _Mt = modular_t<T, M_>;
  using ll = long long;

private:
  int n_;
  std::vector<_Mt> fact, ifact;
};
// clang-format on
