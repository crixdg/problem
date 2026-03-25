/**
 *    author: crixdg
 *    modified: 25.03.2026 15:34:46
 *    created: 25.03.2026 12:08:30
 **/
#include "modular.cc"
#include <bits/stdc++.h>

// --------------------- COMBINATORICS (PRIME MODULUS) --------------------------

/** combinatorics class for prime modulus **/
/** requires P_ to be a prime number **/
template <integer_c T, T *P_, int MAX_N_>
class combinatorics_prime_t {
public:
  using ll = long long;
  using _Mt = modular_t<T, P_>;
  combinatorics_prime_t() : n_(0), fact_(1, _Mt(1)), ifact_(1, _Mt(1)) {}
  combinatorics_prime_t(int n) : n_(0), fact_(1, _Mt(1)), ifact_(1, _Mt(1)) { extend(n); }

  void extend(ll n) {
    n = static_cast<int>(std::min(n, std::min<ll>(*P_ - 1, MAX_N_)));
    if (n <= n_) { return; }
    fact_.resize(n + 1), ifact_.resize(n + 1);
    for (int i = n_ + 1; i <= n; i++) {
      fact_[i] = fact_[i - 1] * i;
    }
    ifact_[n] = inverse(fact_[n], *P_);
    for (int i = n - 1; i > n_; i--) {
      ifact_[i] = ifact_[i + 1] * (i + 1);
    }
    n_ = n;
  }

  _Mt C(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    extend(n);
    if (n <= n_) { return fact_[n] * ifact_[k] * ifact_[n - k]; }
    return C(n % *P_, k % *P_) * C(n / *P_, k / *P_);
  }

  _Mt P(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    extend(n);
    if (n <= n_) { return fact_[n] * ifact_[n - k]; }
    if (k >= *P_) { return _Mt(0); }
    assert(k <= n_);
    return C(n, k) * fact_[k];
  }

private:
  int n_;
  std::vector<_Mt> fact_, ifact_;
};

using comb_pr_t = combinatorics_prime_t<mod_t, &md, int(2e7)>;
// clang-format on

// --------------------- COMBINATORICS (PRIME^K MODULUS) --------------------------

/** combinatorics class for prime^e modulus **/
/** requires M_ to be a prime^e number **/
template <integer_c T, T *M_, T P_, int MAX_N_>
class combinatorics_prime_power_t {
public:
  using _Mt = modular_t<T, M_>;
  using ll = long long;
  combinatorics_prime_power_t() {
    pfree_n_ = std::min(*M_ - 1, MAX_N_);
    pfree_.resize(pfree_n_ + 1);
    pfree_[0] = _Mt(1);
    for (int i = 1; i <= E_; i++) {
      pfree_[i] = pfree_[i - 1] * P_;
    }
  }

  _Mt C(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    ll v = vp(n) - vp(k) - vp(n - k);
    ll s = n / (*M_) - k / (*M_) - (n - k) / (*M_);
    if (v >= E_) { return _Mt(0); }
    _Mt pfree_ifact_k = pfree_fact(k).inverse();
    _Mt pfree_ifact_nk = pfree_fact(n - k).inverse();
    _Mt ans = pfree_fact(n) * pfree_ifact_k * pfree_ifact_nk * mod_power<T>(P_, v, *M_);
    return s % 2 == 0 ? ans : -ans;
  }

private:
  int pfree_n_;
  std::vector<_Mt> pfree_;

  static constexpr int E_ = []() {
    int e = 0;
    T m = *M_, p = P_;
    while (m % p == 0) { m /= p, e++; }
    return e;
  }();

  // legendre / p-adic valuation of n!
  ll vp(ll n) {
    ll v = 0;
    while (n >= P_) { n /= P_, v += n; }
    return v;
  }

  _Mt pfree_fact(ll n) {
    if (n == 0) {
      return _Mt(1);
    }
    _Mt ans = mod_power<T>();
    return ans;
  }
};

using comb_pp_t = combinatorics_prime_power_t<mod_t, &md, 2, int(2e7)>;
// clang-format on

// --------------------- COMBINATORICS (ARBITRARY MODULUS) --------------------------

/** combinatorics class for arbitrary modulus **/
/** requires M_ to be a prime number **/
// clang-format on
