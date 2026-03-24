#include <bits/stdc++.h>
template <typename T>
concept integer_c = std::same_as<T, int> || std::same_as<T, long> || std::same_as<T, long long> ||
                    (requires { typename T::is_custom_integral; } && requires(T a, T b, const T &ca, const T &cb, std::istream &is, std::ostream &os) {
                      T();
                      { is >> a } -> std::same_as<std::istream &>;
                      { os << ca } -> std::same_as<std::ostream &>;

                      { ca + cb } -> std::convertible_to<T>;
                      { ca - cb } -> std::convertible_to<T>;
                      { ca * cb } -> std::convertible_to<T>;
                      { ca / cb } -> std::convertible_to<T>;
                      { ca % cb } -> std::convertible_to<T>;
                      { -ca } -> std::convertible_to<T>;

                      { ca & cb } -> std::convertible_to<T>;
                      { ca | cb } -> std::convertible_to<T>;
                      { ca ^ cb } -> std::convertible_to<T>;
                      { ca << cb } -> std::convertible_to<T>;
                      { ca >> cb } -> std::convertible_to<T>;
                      { ~ca } -> std::convertible_to<T>;


                      { ca == cb } -> std::convertible_to<bool>;
                      { ca != cb } -> std::convertible_to<bool>;
                      { ca < cb } -> std::convertible_to<bool>;
                      { ca > cb } -> std::convertible_to<bool>;
                      { ca <= cb } -> std::convertible_to<bool>;
                      { ca >= cb } -> std::convertible_to<bool>;


                      { a %= cb } -> std::convertible_to<T>; });

template <typename T, typename U>
struct wider;

template <typename T, typename U>
concept compatible_integer_c = integer_c<T> && integer_c<U> && (requires { typename wider<T, U>::type; } && requires(const T &t, const U &u) {
  { static_cast<T>(u) } -> std::convertible_to<T>;
  { static_cast<U>(t) } -> std::convertible_to<U>; });

// default implementation of wider
template <typename T, typename U>
struct wider {
  using type = std::conditional_t<(sizeof(T) < sizeof(U)), U, T>;
};

template <integer_c T, T *_M>
  requires(_M != nullptr)

class modular_t {
public:
  constexpr modular_t() : value_(T()) {}

  template <compatible_integer_c<T> U> modular_t(const U &u) : value_(normalize(u)) {}
  template <compatible_integer_c<T> U> modular_t &operator=(const U &u) {
    value_ = normalize(u);
    return *this;
  }

  // input (cin) operator
  friend std::istream &operator>>(std::istream &is, modular_t &m) {
    T u;
    is >> u;
    m.value_ = normalize(u);
    return is;
  }

  // output (cout) operator
  friend std::ostream &operator<<(std::ostream &os, const modular_t &m) {
    return os << m.value_;
  }

private:
  T value_;

  template <compatible_integer_c<T> U>
  static T normalize(const U &u) {
    using W = wider<T, U>::type;
    W mod = static_cast<W>(*_M), val = static_cast<W>(u);
    if (val <= -mod || val >= mod) { val %= mod; }
    return static_cast<T>(val < W() ? val + mod : val);
  }
};

class my_int {
public:
  using is_custom_integral = std::true_type;
  my_int() : value_(0) {}

  friend std::istream &operator>>(std::istream &is, my_int &m) { return is >> m.value_; }
  friend std::ostream &operator<<(std::ostream &os, const my_int &m) { return os << m.value_; }

  friend my_int operator+(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ + rhs.value_); }
  friend my_int operator-(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ - rhs.value_); }
  friend my_int operator*(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ * rhs.value_); }
  friend my_int operator/(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ / rhs.value_); }
  friend my_int operator%(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ % rhs.value_); }
  friend my_int operator-(const my_int &rhs) { return my_int(-rhs.value_); }

  friend my_int operator&(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ & rhs.value_); }
  friend my_int operator|(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ | rhs.value_); }
  friend my_int operator^(const my_int &lhs, const my_int &rhs) { return my_int(lhs.value_ ^ rhs.value_); }

  my_int &operator%=(const my_int &other) {
    value_ %= other.value_;
    return *this;
  }

  // compatible
  operator int() const { return value_; }

  // extra
  my_int(int x) : value_(x) {}

private:
  int value_;
};
static_assert(integer_c<my_int>);

using mod_t = my_int;
mod_t md = 1e9 + 7;
using mint_t = modular_t<mod_t, &md>;

int main() {
  std::cin >> md;
  std::cout << md << '\n';

  mint_t a = 1;
  // int b = 2;
  // a = b;
  std::cout << a << '\n';
  // std::cin >> a;
  // std::cout << a << '\n';
  return 0;
}
