/**
 *    author: crixdg
 *    modified: 26.03.2026 12:23:09
 *    created: 26.03.2026 12:19:22
 **/
#include <bits/stdc++.h>

// clang-format off
template<typename T, auto EPS_ = T(1e-9)>
requires std::same_as<T, double> || std::same_as<T, long double>
class vector_t {
public:
  constexpr vector_t() : x_(0), y_(0) {}
  constexpr vector_t(T x, T y) : x_(x), y_(y) {}
  constexpr vector_t(const vector_t &) = default;

  T x() const { return x_; }
  T y() const { return y_; }

  T dot(const vector_t &other) const { return x_ * other.x_ + y_ * other.y_; }
  T cross(const vector_t &other) const { return x_ * other.y_ - y_ * other.x_; }
  T norm2() const { return dot(*this); }
  T norm() const { return std::sqrt(norm2()); }
  T angle() const { return std::atan2(y_, x_); }
  T angle_degree() const { return std::atan2(y_, x_) * T(180) / std::numbers::pi_v<T>; }

  vector_t perp() const { return vector_t(y_, -x_); }
  vector_t unit() const { return *this / norm(); }
  vector_t operator-() const { return vector_t(-x_, -y_); }

  vector_t &operator+=(const vector_t &other) { x_ += other.x_, y_ += other.y_; return *this; }
  vector_t &operator-=(const vector_t &other) { x_ -= other.x_, y_ -= other.y_; return *this; }
  vector_t &operator*=(T scalar) { x_ *= scalar, y_ *= scalar; return *this; }
  vector_t &operator/=(T scalar) { assert(abs(scalar) > EPS_); x_ /= scalar, y_ /= scalar; return *this; }

  friend bool operator==(const vector_t &lhs, const vector_t &rhs) {
    return lhs.approx_eq(lhs.x_, rhs.x_) && lhs.approx_eq(lhs.y_, rhs.y_);
  }

  friend std::ostream &operator<<(std::ostream &os, const vector_t &v) { return os << v.x_ << ' ' << v.y_; }
  friend std::istream &operator>>(std::istream &is, vector_t &v) { return is >> v.x_ >> v.y_; }

  friend vector_t operator+(const vector_t &lhs, const vector_t &rhs) { return vector_t(lhs) += rhs; }
  friend vector_t operator-(const vector_t &lhs, const vector_t &rhs) { return vector_t(lhs) -= rhs; }
  friend vector_t operator*(const vector_t &lhs, T scalar) { return vector_t(lhs) *= scalar; }
  friend vector_t operator*(T scalar, const vector_t &rhs) { return rhs * scalar; }
  friend vector_t operator/(const vector_t &lhs, T scalar) { return vector_t(lhs) /= scalar; }

  /** |a-b| <= EPS_ * max(1, |a|, |b|) */
  static bool approx_eq(T a, T b) {
    return std::abs(a - b) <= EPS_ * std::max({T(1), std::abs(a), std::abs(b)});
  }

private:
  T x_, y_;
};


using t_ = double;
constexpr t_ EPS_ = 1e-9;
using vec_t = vector_t<t_, EPS_>;
constexpr auto vec_cmp = [](const vec_t &a, const vec_t &b) {
  if (!vec_t::approx_eq(a.x(), b.x())) return a.x() < b.x();
  if (!vec_t::approx_eq(a.y(), b.y())) return a.y() < b.y();
  return false;
};

// clang-format on
