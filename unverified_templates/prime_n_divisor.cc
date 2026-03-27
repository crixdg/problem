/**
 *    author: crixdg
 *    modified: 26.03.2026 12:31:10
 *    created: 25.03.2026 22:08:43
 **/
#include <bits/stdc++.h>

using namespace std;

template <typename T>
concept integer_c = same_as<T, int> || same_as<T, long> || same_as<T, long long>;

/** modular exponentiation **/
template <integer_c T>
T mod_power(T a, long long b, T m) {
  assert(m > 0);
  bool is_negative_power = b < 0;
  if (is_negative_power) {
    b = -b, a = mod_inverse<T>(a, m);
    assert(a != T(-1));
  }
  T ans = 1;
  a %= m;
  while (b != 0) {
    if (b & 1) { ans = ((__int128_t)ans * a) % m; }
    a = ((__int128_t)a * a) % m;
    b >>= 1;
  }
  return ans;
}

/** miller-rabin primality test **/
template <integer_c T>
bool miller_test(T a, T d, T n, int s) {
  T x = mod_power<T>(a, d, n);
  if (x == 1 || x == n - 1) { return true; }
  for (int i = 0; i < s - 1; i++) {
    x = ((__int128_t)x * x) % n;
    if (x == n - 1) { return true; }
  }
  return false;
}

/** is_prime **/
template <integer_c T>
bool is_prime(T n) {
  if (n < 2) { return false; }
  if (n == 2 || n == 3) { return true; }
  if (n % 2 == 0 || n % 3 == 0) { return false; }

  T d = n - 1;
  int s = 0;
  while (d % 2 == 0) { d >>= 1, ++s; }

  for (T a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (a >= n) { break; }
    if (!miller_test<T>(a, d, n, s)) { return false; }
  }
  return true;
}

/** prime_base_t **/
// clang-format off
template <integer_c T, T MAX_N_>
class prime_base_t {
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

  bool is_prime(T n) const {
    if (n <= MAX_N_) { return spf_[n] == n; }
    throw invalid_argument("n is too large");
  }

  vector<pair<T, int>> prime_factors(T n) const {
    vector<pair<T, int>> factors;
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

  // D = (1 + e_1) * (1 + e_2) * ... * (1 + e_n) with n = p_1^e_1 * p_2^e_2 * ... * p_n^e_n
  int no_of_divisors(T n) const {
    int ans = 1;
    while (n > 1) {
      T t = spf_[n];
      int c = 0;
      while (spf_[n] == t) { c++, n /= spf_[n]; }
      ans *= c + 1;
    }
    return ans;
  }

  // S = BigPi_1^k( (pi^(ei+1) - 1)/(pi-1) )
  ll sum_of_divisors(T n) const {
    ll ans = n;
    while (n > 1) {
      T t = spf_[n];
      ll u = 1, v = ans;
      while (spf_[n] == t) {
        u *= t;
        v += ans / u;
        n /= spf_[n];
      }
      ans = v;
    }
    return ans;
  }

  // P = n^(D/2)
  ll prod_of_divisors(T n) const {
    int d = no_of_divisors(n);
    __int128_t a = n;
    if (d & 1) { a = sqrtl(a); }
    else { d >>= 1; }

    ll ans = 1;
    while (d > 0) {
      if (d & 1) { ans *= a; }
      d >>= 1;
      a *= a;
    }
    return ans;
  }

  // S2 = BigSigma_1^n( n/i * i )
  ll sum_of_sum_of_divisors(T n) const {
    ll ans = 0;
    for (T i = 1; (ll)i * i <= n; i++) {
      ans += (n / i) * i;
      if (i != n / i) { ans += (n / i) * (n / i) * i / (n / i); }
    }
    return ans;
  }

private:
  vector<T> spf_;
};

using prime_base = prime_base_t<int, int(1e7)>;
// clang-format on
