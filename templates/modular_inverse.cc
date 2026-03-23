#include <bits/stdc++.h>

/** author: crixdg, created: 2026-03-23
 * * modular inverse of a_ modulo m_ if exists, otherwise -1
 * * based on Extended Euclidean Algorithm
 * requires:
 * * a_ and m_ are coprime
 * * m_ is positive
 **/
template <std::integral _An, std::integral _Mn>
  requires(std::same_as<_An, int> || std::same_as<_An, long long>) &&
          (std::same_as<_Mn, int> || std::same_as<_Mn, long long>)
constexpr std::common_type_t<_An, _Mn> modular_inverse(_An a, _Mn m) {
  using _Ct = std::common_type_t<_An, _Mn>;
  if (m <= 0) {
    return _Ct(-1);
  }

  using ll = long long;
  ll a2 = (a % m + m) % m;
  ll m2 = m, orig_m = m2;
  ll u = 0, v = 1;
  while (a2 != 0) {
    ll t = m2 / a2;
    m2 -= t * a2, std::swap(m2, a2);
    u -= t * v, std::swap(u, v);
  }

  if (m2 != 1) {
    return _Ct(-1);
  }
  return _Ct(u < 0 ? u + orig_m : u);
}
