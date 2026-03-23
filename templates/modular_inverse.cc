#include <bits/stdc++.h>

/** author: crixdg, created: 2026-03-23
 * modular inverse of __a modulo __m
 * using Extended Euclidean Algorithm
 *
 * requires:
 * * __a and __m are coprime
 * * both __a and __m are signed integers
 * * __m is positive
 **/
template <std::integral _An, std::integral _Mn>
  requires(std::same_as<_An, int> || std::same_as<_An, long long>) &&
          (std::same_as<_Mn, int> || std::same_as<_Mn, long long>)
constexpr std::common_type_t<_An, _Mn>
modular_inverse(_An __a, _Mn __m) {
  assert(__m > 0);
  using _Ct = std::common_type_t<_An, _Mn>;
  _Ct __a2 = (_Ct(__a) % _Ct(__m) + _Ct(__m)) % _Ct(__m);
  _Ct __m2 = _Ct(__m), __orig_m = __m2;
  _Ct __u = 0, __v = 1;
  while (__a2 != 0) {
    _Ct __t = __m2 / __a2;
    __m2 -= __t * __a2, std::swap(__m2, __a2);
    __u -= __t * __v, std::swap(__u, __v);
  }
  assert(__m2 == 1);
  return __u < 0 ? __u + __orig_m : __u;
}
