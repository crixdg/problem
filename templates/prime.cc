#include "modular.cc"
#include <bits/stdc++.h>

template <integer_c T, T MAX_N_>
class prime_base {
public:
  using ll = long long;
  void spf_sieve() {
    spf_.resize(MAX_N_ + 1);
    iota(begin(spf_), end(spf_), T(0));
    for (T i = 2; i <= MAX_N_; i++) {
      if (spf_[i] == i) {
        for (__int128_t j = (__int128_t)i * i; j <= MAX_N_; j += i) {
          if (spf_[j] == j) { spf_[j] = i; }
        }
      }
    }
  }

  bool miller_test(T a, long long d, T n, int s) {
    T x = mod_power<T>(a, d, n);
    if (x == 1 || x == n - 1) { return true; }
    for (int i = 0; i < s - 1; ++i) {
      x = ((__int128)x * x) % n;
      if (x == n - 1) { return true; }
    }
    return false;
  }

  bool is_prime(T n) {
    if (n < 2) { return false; }
    if (n % 2 == 0) { return n == 2; }
    T d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d >>= 1, ++s; }

    std::vector<T> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (T a : bases) {
      if (a >= n) { break; }
      if (!miller_test(a, d, n, s)) { return false; }
    }
    return true;
  }

  std::vector<std::pair<T, int>> prime_factors(T n) const {
    std::vector<std::pair<T, int>> factors;
    T t = -1;
    int c = 0;
    while (n > 1) {
      if (spf_[n] != t) {
        if (t != T(-1)) { factors.emplace_back(t, c); }
        t = spf_[n], c = 1;
      } else {
        c++;
      }
      n /= spf_[n];
    }
    if (t != T(-1)) { factors.emplace_back(t, c); }
    return factors;
  }

private:
  std::vector<T> spf_;
};
