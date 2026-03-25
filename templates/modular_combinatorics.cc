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
template <integer_c T, T *P_, int MAX_FACT_N_>
class combinatorics_prime_t {
public:
  using ll = long long;
  using _Mt = modular_t<T, P_>;
  combinatorics_prime_t() : fact_n_(1), fact_(1, _Mt(1)), ifact_(1, _Mt(1)) {}
  combinatorics_prime_t(int n) : fact_n_(1), fact_(1, _Mt(1)), ifact_(1, _Mt(1)) { extend(n); }

  void extend(ll n) {
    n = static_cast<int>(std::min(n, std::min<ll>(*P_ - 1, MAX_FACT_N_)));
    if (n < fact_n_) { return; }
    fact_.resize(n + 1), ifact_.resize(n + 1);
    for (int i = fact_n_; i <= n; i++) {
      fact_[i] = fact_[i - 1] * i;
    }
    ifact_[n] = fact_[n].inverse();
    for (int i = n - 1; i >= fact_n_; i--) {
      ifact_[i] = ifact_[i + 1] * (i + 1);
    }
    fact_n_ = n + 1;
  }

  _Mt C(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    extend(n);
    if (n < fact_n_) { return fact_[n] * ifact_[k] * ifact_[n - k]; }
    return C(n % *P_, k % *P_) * C(n / *P_, k / *P_);
  }

  _Mt P(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    extend(n);
    if (n < fact_n_) { return fact_[n] * ifact_[n - k]; }
    if (k >= *P_) { return _Mt(0); }
    assert(k < fact_n_);
    return C(n, k) * fact_[k];
  }

private:
  int fact_n_;
  std::vector<_Mt> fact_, ifact_;
};

using comb_pr_t = combinatorics_prime_t<mod_t, &md, int(2e7)>;
// clang-format on

// --------------------- COMBINATORICS (PRIME^K MODULUS) --------------------------

/** combinatorics class for prime^e modulus **/
/** requires M_ to be a prime^e number **/
template <integer_c T, T *M_, T P_, int MAX_PFREE_N_>
class combinatorics_prime_power_t {
public:
  using _Mt = modular_t<T, M_>;
  using ll = long long;
  combinatorics_prime_power_t() {
    assert(*M_ > 0);
    pfree_n_ = static_cast<int>(std::min<T>(*M_, MAX_PFREE_N_ + 1));
    pfree_.resize(pfree_n_);
    pfree_[0] = _Mt(1);
    for (int i = 1; i < pfree_n_; i++) {
      T x = i;
      while (x % P_ == 0) { x /= P_; }
      pfree_[i] = pfree_[i - 1] * x;
    }
  }

  _Mt C(ll n, ll k) {
    if (k < 0 || k > n) { return _Mt(0); }
    ll v = vp(n) - vp(k) - vp(n - k);
    if (v >= E_) { return _Mt(0); }
    _Mt pfree_ifact_k = pfree_fact(k).inverse();
    _Mt pfree_ifact_nk = pfree_fact(n - k).inverse();
    return pfree_fact(n) * pfree_ifact_k * pfree_ifact_nk * mod_power<T>(P_, v, *M_);
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

  static constexpr int S_ = []() {
    if constexpr (P_ != 2) {
      return -1;
    } else {
      if (E_ == 1) {
        return 1;
      }
      if (E_ == 2) {
        return -1;
      }
      return 1;
    }
  }();

  // legendre's formula / p-adic valuation of n!
  ll vp(ll n) {
    ll v = 0;
    while (n >= P_) { n /= P_, v += n; }
    return v;
  }

  // granville's formula / p-free factorial
  _Mt pfree_fact(ll n) {
    if (n == 0) { return _Mt(1); }
    assert(n % *M_ < pfree_n_);
    _Mt ans = pfree_[n % *M_] * pfree_fact(n / P_);
    return (n / (*M_)) % 2 == 0 ? ans : ans * S_;
  }
};

using comb_pp_t = combinatorics_prime_power_t<mod_t, &md, 2, int(2e7)>;
// clang-format on

// --------------------- COMBINATORICS (ARBITRARY MODULUS) --------------------------

/** combinatorics class for arbitrary modulus **/
/** requires M_ to be a prime number **/
// clang-format on
