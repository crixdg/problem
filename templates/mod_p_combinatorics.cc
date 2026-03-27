/**
 *    author: crixdg
 *    timestamp: 28.03.2026 03:19:08
 **/

#include "modular.cc"
#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- COMBINATORICS (PRIME MODULUS) ----------------------------- **/

template <integer_c T, T *P_, int MAX_FACT_N_ = int(2e7)>
class combinatorics_prime_t {
public:
  using ll = long long;
  using _Mt = modular_t<T, P_>;
  combinatorics_prime_t() {}
  combinatorics_prime_t(int n) { extend(n); }

  void extend(ll n) {
    n = static_cast<int>(min(n, min<ll>(*P_ - 1, MAX_FACT_N_)));
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
  int fact_n_{0};
  vector<_Mt> fact_{1, _Mt(1)}, ifact_{1, _Mt(1)};
};

using comb_pr_t = combinatorics_prime_t<mod_t, &md, int(2e7)>;
