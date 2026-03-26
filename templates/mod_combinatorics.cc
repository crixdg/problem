/**
 *    author: crixdg
 *    modified: 26.03.2026 12:24:41
 *    created: 25.03.2026 12:08:30
 **/
#include "modular.cc"
#include <bits/stdc++.h>

// --------------------- COMBINATORICS (PRIME MODULUS) --------------------------

/** combinatorics class for prime modulus **/
// clang-format off
template <integer_c T, T *P_, int MAX_FACT_N_ = int(2e7)>
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
    assert(k < fact_n_); return C(n, k) * fact_[k];
  }

private:
  int fact_n_; std::vector<_Mt> fact_, ifact_;
};

using comb_pr_t = combinatorics_prime_t<mod_t, &md, int(2e7)>;
// clang-format on

// --------------------- COMBINATORICS (PRIME^K MODULUS) --------------------------

/** combinatorics class for prime^e modulus **/
/** requires M_ to be a prime^e number **/
// clang-format off
template <integer_c T, T *M_, T P_, int MAX_PFREE_N_ = int(2e7)>
class combinatorics_prime_power_t {
public:
  using _Mt = modular_t<T, M_>;
  using ll = long long;
  combinatorics_prime_power_t() {
    assert(*M_ > 0 && *M_ <= MAX_PFREE_N_);
    pfree_.resize(static_cast<int>(*M_));
    pfree_[0] = _Mt(1);
    for (int i = 1; i < static_cast<int>(*M_); i++) {
      T t = i;
      while (t % P_ == 0) { t /= P_; }
      pfree_[i] = pfree_[i - 1] * t;
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
  std::vector<_Mt> pfree_;

  static constexpr int E_ = []() {
    int e = 0;
    T m = *M_, p = P_;
    while (m % p == 0) { m /= p, e++; }
    return e;
  }();

  // legendre's formula / p-adic valuation of n!
  ll vp(ll n) {
    ll v = 0;
    while (n >= P_) { n /= P_, v += n; }
    return v;
  }

  // granville's formula / p-free factorial
  _Mt pfree_fact(ll n) {
    _Mt ans = _Mt(1);
    while (n > 0) {
      ans *= pfree_[n % *M_];
      if ((n / (*M_)) % 2 == 1) { ans *= pfree_[*M_ - 1]; }
      n /= (*M_);
    }
    return ans;
  }
};

template <mod_t P> using comb_pp_t = combinatorics_prime_power_t<mod_t, &md, P, int(2e7)>;
// clang-format on

// --------------------- COMBINATORICS (ARBITRARY MODULUS) --------------------------

// TODO: Chinese Remainder Theorem
/** combinatorics class for arbitrary modulus **/
// clang-format off
template <integer_c T, T *M_>
class combinatorics_arbitrary_t {
public:
  using _Mt = modular_t<T, M_>;
  combinatorics_arbitrary_t() {}
  combinatorics_arbitrary_t(int n) {}
};

using comb_ar_t = combinatorics_arbitrary_t<mod_t, &md>;
// clang-format on
