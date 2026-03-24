#include <bits/stdc++.h>
template <typename T>
concept modular_base = requires(T a, T b) {
  // arithmetic
  { a + b } -> std::convertible_to<T>;
  { a - b } -> std::convertible_to<T>;
  { a * b } -> std::convertible_to<T>;
  { a / b } -> std::convertible_to<T>;
  { a % b } -> std::convertible_to<T>;
  { -a } -> std::convertible_to<T>;
  // increment/decrement
  { a++ } -> std::convertible_to<T>;
  { a-- } -> std::convertible_to<T>;
  { ++a } -> std::convertible_to<T>;
  { --a } -> std::convertible_to<T>;
  // bitwise
  { a & b } -> std::convertible_to<T>;
  { a | b } -> std::convertible_to<T>;
  { a ^ b } -> std::convertible_to<T>;
  { a << b } -> std::convertible_to<T>;
  { a >> b } -> std::convertible_to<T>;
  { ~a } -> std::convertible_to<T>;
  // assignment
  { a = b } -> std::convertible_to<T>;
  { a += b } -> std::convertible_to<T>;
  { a -= b } -> std::convertible_to<T>;
  { a *= b } -> std::convertible_to<T>;
  { a /= b } -> std::convertible_to<T>;
  { a %= b } -> std::convertible_to<T>;
  { a &= b } -> std::convertible_to<T>;
  { a |= b } -> std::convertible_to<T>;
  { a ^= b } -> std::convertible_to<T>;
  { a <<= b } -> std::convertible_to<T>;
  { a >>= b } -> std::convertible_to<T>;
  // comparison operations
  { a == b } -> std::convertible_to<bool>;
  { a != b } -> std::convertible_to<bool>;
  { a < b } -> std::convertible_to<bool>;
  { a > b } -> std::convertible_to<bool>;
  { a <= b } -> std::convertible_to<bool>;
  { a >= b } -> std::convertible_to<bool>;
  // casting
  { static_cast<__int128_t>(a) } -> std::same_as<__int128_t>;
  // constructible
  T(0), T(1);
};

template <modular_base T, T *mod, >

using mod_t = int;
mod_t md = 1e9 + 7;
using mint_t = modular_t<mod_t, &md>;

int main() {
  std::cin >> md;
  return 0;
}
