/**
 *    author: crixdg
 *    modified: 25.03.2026 01:06:22
 *    created: 23.03.2026 10:02:41
 *    description: modular arithmetic and combinatorics
 **/
#include <bits/stdc++.h>

template <typename T>
concept integer_c = std::same_as<T, int> || std::same_as<T, long> || std::same_as<T, long long>;

// --------------------- MODULAR ARITHMETIC --------------------------

/** modular inverse **/
template <integer_c T>
T mod_inverse(T a, T m) {
  assert(m > 0);
  __int128_t orig_m = m, u = 0, v = 1;
  a %= m, a = a < 0 ? a + m : a;
  while (a != 0) {
    T t = m / a;
    m -= a * t, std::swap(m, a);
    u -= v * t, std::swap(u, v);
  }
  if (m != 1) { return T(-1); }
  return static_cast<T>(u < __int128_t(0) ? u + orig_m : u);
}

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

/** modular class **/
// clang-format off
template <integer_c T, T *M_>
class modular_t {
public:
  constexpr modular_t() : value_(T(0)) {}
  constexpr modular_t(const modular_t &other) : value_(other.value_) {}
  template <integer_c U> modular_t(const U &u) : value_(normalize(u)) {}

  static T mod() { return *M_; }
  T operator()() const { return value_; }

  template <integer_c U> explicit operator U() const { return static_cast<U>(value_); }
  friend std::string to_string(const modular_t &m) { return std::to_string(m.value_); }

  template <typename U> friend U &operator>>(U &is, modular_t &m) { T u; is >> u; m.value_ = normalize(u); return is; }
  template <typename U> friend U &operator<<(U &os, const modular_t &m) { return os << m.value_; }

  modular_t &operator=(const modular_t &other) { value_ = other.value_; return *this; }
  template <integer_c U> modular_t &operator=(const U &u) { return *this = modular_t(u); }

  modular_t &operator+=(const modular_t &other) { value_ = add(value_, other.value_); return *this; }
  template <integer_c U> modular_t &operator+=(const U &u) { return *this += modular_t(u); }

  modular_t &operator-=(const modular_t &other) { value_ = sub(value_, other.value_); return *this; }
  template <integer_c U> modular_t &operator-=(const U &u) { return *this -= modular_t(u); }

  modular_t &operator*=(const modular_t &other) { value_ = mul(value_, other.value_); return *this; }
  template <integer_c U> modular_t &operator*=(const U &u) { return *this *= modular_t(u); }

  modular_t &operator/=(const modular_t &other) { value_ = div(value_, other.value_); return *this; }
  template <integer_c U> modular_t &operator/=(const U &u) { return *this /= modular_t(u); }

  modular_t &operator++() { return *this += 1; }
  modular_t &operator--() { return *this -= 1; }
  modular_t operator++(int) { modular_t result(*this); *this += 1; return result; }
  modular_t operator--(int) { modular_t result(*this); *this -= 1; return result; }
  modular_t operator-() const { return value_ == 0 ? modular_t() : modular_t(-value_); }

  friend modular_t operator+(const modular_t &lhs, const modular_t &rhs) { return modular_t(lhs) += rhs; }
  template <integer_c U> friend modular_t operator+(const modular_t &lhs, U rhs) { return modular_t(lhs) += rhs; }
  template <integer_c U> friend modular_t operator+(U lhs, const modular_t &rhs) { return modular_t(lhs) += rhs; }

  friend modular_t operator-(const modular_t &lhs, const modular_t &rhs) { return modular_t(lhs) -= rhs; }
  template <integer_c U> friend modular_t operator-(const modular_t &lhs, U rhs) { return modular_t(lhs) -= rhs; }
  template <integer_c U> friend modular_t operator-(U lhs, const modular_t &rhs) { return modular_t(lhs) -= rhs; }

  friend modular_t operator*(const modular_t &lhs, const modular_t &rhs) { return modular_t(lhs) *= rhs; }
  template <integer_c U> friend modular_t operator*(const modular_t &lhs, U rhs) { return modular_t(lhs) *= rhs; }
  template <integer_c U> friend modular_t operator*(U lhs, const modular_t &rhs) { return modular_t(lhs) *= rhs; }

  friend modular_t operator/(const modular_t &lhs, const modular_t &rhs) { return modular_t(lhs) /= rhs; }
  template <integer_c U> friend modular_t operator/(const modular_t &lhs, U rhs) { return modular_t(lhs) /= rhs; }
  template <integer_c U> friend modular_t operator/(U lhs, const modular_t &rhs) { return modular_t(lhs) /= rhs; }

  friend bool operator==(const modular_t &lhs, const modular_t &rhs) { return lhs.value_ == rhs.value_; }
  template <integer_c U> friend bool operator==(const modular_t &lhs, U rhs) { return lhs == modular_t(rhs); }
  template <integer_c U> friend bool operator==(U lhs, const modular_t &rhs) { return modular_t(lhs) == rhs; }

  friend bool operator!=(const modular_t &lhs, const modular_t &rhs) { return !(lhs == rhs); }
  template <integer_c U> friend bool operator!=(const modular_t &lhs, U rhs) { return !(lhs == rhs); }
  template <integer_c U> friend bool operator!=(U lhs, const modular_t &rhs) { return !(lhs == rhs); }

  friend bool operator<(const modular_t &lhs, const modular_t &rhs) { return lhs.value_ < rhs.value_; }
  template <integer_c U> friend bool operator<(const modular_t &lhs, U rhs) { return lhs < modular_t(rhs); }
  template <integer_c U> friend bool operator<(U lhs, const modular_t &rhs) { return modular_t(lhs) < rhs; }

  friend bool operator>(const modular_t &lhs, const modular_t &rhs) { return lhs.value_ > rhs.value_; }
  template <integer_c U> friend bool operator>(const modular_t &lhs, U rhs) { return lhs > modular_t(rhs); }
  template <integer_c U> friend bool operator>(U lhs, const modular_t &rhs) { return modular_t(lhs) > rhs; }

  friend bool operator>=(const modular_t &lhs, const modular_t &rhs) { return !(lhs.value_ < rhs.value_); }
  template <integer_c U> friend bool operator>=(const modular_t &lhs, U rhs) { return !(lhs < rhs); }
  template <integer_c U> friend bool operator>=(U lhs, const modular_t &rhs) { return !(lhs < rhs); }

  friend bool operator<=(const modular_t &lhs, const modular_t &rhs) { return !(lhs.value_ > rhs.value_); }
  template <integer_c U> friend bool operator<=(const modular_t &lhs, U rhs) { return !(lhs > rhs); }
  template <integer_c U> friend bool operator<=(U lhs, const modular_t &rhs) { return !(lhs > rhs); }

  friend modular_t power(const modular_t &lhs, long long rhs, T m) { return mod_power<T>(lhs(), rhs, m); }
  friend modular_t inverse(const modular_t &lhs, T m) { return mod_inverse<T>(lhs(), m); }

private:
  T value_;

  static T normalize(__int128_t val) {
    __int128_t md = static_cast<__int128_t>(*M_);
    val %= md; return static_cast<T>(val < __int128_t(0) ? val + md : val);
  }

  static T add(__int128_t a, __int128_t b) { return normalize(a + b); }
  static T sub(__int128_t a, __int128_t b) { return normalize(a - b); }
  static T mul(__int128_t a, __int128_t b) { return normalize(a * b); }
  static T div(__int128_t a, __int128_t b) { T inv = mod_inverse<T>(b, *M_); assert(inv != T(-1)); return mul(a, inv); }
};

using mod_t = int; mod_t md = 1e9 + 7;
using mint_t = modular_t<mod_t, &md>;
// clang-format on

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
