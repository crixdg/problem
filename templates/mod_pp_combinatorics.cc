#include "modular.cc"
#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- COMBINATORICS (PRIME POWER MODULUS) ----------------------------- **/

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
  vector<_Mt> pfree_;

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
