#include <bits/stdc++.h>

template <typename T>
class modular_t {
  using type_t = typename std::decay<decltype(T::value)>::type;

  constexpr modular_t() noexcept : __v() {}

  template <typename V>
  modular_t(const V &v) noexcept : __v(normalize(v)) {}

  template <typename U>
  type_t normalize(const U &__u) {
    type_t __val;
    type_t __md = mod();

    if (-__md <= __u && __u < __md) {
      __val = static_cast<type_t>(__u);
    } else {
      __val = static_cast<type_t>(__u % __md);
    }

    return __val < 0 ? __val + __md : __val;
  }

  constexpr static type_t mod() { return T::value; }

  modular_t &operator+=(const modular_t &__o) {
    if ((__v += __o.__v) >= mod()) {
      __v -= mod();
    }
    return *this;
  }

  modular_t &operator-=(const modular_t &__o) {
    if ((__v -= __o.__v) < 0) {
      __v += mod();
    }
    return *this;
  }

private:
  type_t __v;
};

using mod_t = int;
struct var_mod {
  static mod_t value;
};
mod_t var_mod::value = 1e9 + 7;
mod_t &md = var_mod::value;
using mint_t = modular_t<var_mod>;
