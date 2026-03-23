#include <bits/stdc++.h>

template <typename T>
  requires(std::same_as<typename std::decay<decltype(T::value)>::type, int> ||
           std::same_as<typename std::decay<decltype(T::value)>::type, long long>)
class modular_t {
  using ll = long long;
  using type_t = typename std::decay<decltype(T::value)>::type;
  constexpr static type_t mod() { return T::value; }

  constexpr modular_t() noexcept : v_() {}
  template <std::integral _Un>
    requires(std::same_as<_Un, int> || std::same_as<_Un, long long>)
  modular_t(const _Un& u) : v_(normalize(u)) {}

  template <std::integral _Un>
    requires(std::same_as<_Un, int> || std::same_as<_Un, long long>)
  type_t normalize(const _Un& u) {
    ll val, md = mod();
    if (u > -md && u < md) {
      val = static_cast<ll>(u);
    } else {
      val = static_cast<ll>(u % md);
    }
    return static_cast<type_t>(val < 0 ? val + md : val);
  }

private:
  type_t v_;
};

using mod_t = int;
struct var_mod {
  static mod_t value;
};
mod_t var_mod::value = 1e9 + 7;
mod_t &md = var_mod::value;
using mint_t = modular_t<var_mod>;
