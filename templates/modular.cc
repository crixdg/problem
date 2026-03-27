/**
 *    author: crixdg
 *    timestamp: 27.03.2026 13:52:10
 **/

#include <bits/stdc++.h>

using namespace std;

// --------------------- MODULAR ARITHMETIC --------------------------

template <typename T>
concept integer_c = same_as<T, int> || same_as<T, long> || same_as<T, long long>;

/** modular inverse **/
template <integer_c T>
T mod_inverse(T a, T m) {
  assert(m > 0);
  __int128_t orig_m = m, u = 0, v = 1;
  a %= m, a = a < 0 ? a + m : a;
  while (a != 0) {
    T t = m / a;
    m -= a * t, swap(m, a);
    u -= v * t, swap(u, v);
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

// clang-format off
template <integer_c T, T *M_>
class modular_t {
public:
  constexpr modular_t() : value_(T(0)) {}
  constexpr modular_t(const modular_t &other) : value_(other.value_) {}
  template <integer_c U> modular_t(const U &u) : value_(normalize(u)) {}

  static T mod() { return *M_; }
  T value() const { return value_; }

  template <integer_c U> explicit operator U() const { return static_cast<U>(value_); }
  friend string to_string(const modular_t &m) { return to_string(m.value_); }

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

  friend auto operator<=>(const modular_t &lhs, const modular_t &rhs) { return lhs.value_ <=> rhs.value_; }
  template <integer_c U> friend auto operator<=>(const modular_t &lhs, U rhs) { return lhs <=> modular_t(rhs); }
  template <integer_c U> friend auto operator<=>(U lhs, const modular_t &rhs) { return modular_t(lhs) <=> rhs; }

  modular_t power(long long rhs) { return mod_power<T>(value_, rhs, *M_); }
  modular_t inverse() { return mod_inverse<T>(value_, *M_); }

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
// clang-format on

using mod_t = int;
mod_t md = 1e9 + 7;
using mint_t = modular_t<mod_t, &md>;
