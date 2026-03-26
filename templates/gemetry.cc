#include <bits/stdc++.h>

// clang-format off
template<typename T, T EPS_ = 1e-9>
requires std::same_as<T, double> || std::same_as<T, long double>
class vector_t {
public:
  constexpr vector_t() : x_(0), y_(0) {}
  constexpr vector_t(T x, T y) : x_(x), y_(y) {}
  vector_t(const vector_t &other) : x_(other.x_), y_(other.y_) {}

  T dot(const vector_t &other) const { return x_ * other.x_ + y_ * other.y_; }
  T cross(const vector_t &other) const { return x_ * other.y_ - y_ * other.x_; }
  T norm2() const { return dot(*this); }
  T norm() const { return std::sqrt(norm2()); }
  T angle() const { return std::atan2(y_, x_); }
  T angle_degree() const { return std::atan2(y_, x_) * 180.0 / M_PI; }

  vector_t &operator+=(const vector_t &other) { x_ += other.x_, y_ += other.y_; return *this; }
  vector_t &operator-=(const vector_t &other) { x_ -= other.x_, y_ -= other.y_; return *this; }
  vector_t &operator*=(T scalar) { x_ *= scalar, y_ *= scalar; return *this; }
  vector_t &operator/=(T scalar) { x_ /= scalar, y_ /= scalar; return *this; }

  vector_t operator-() const { return vector_t(-x_, -y_); }
  vector_t operator~() const { return vector_t(y_, -x_); }

  friend std::ostream &operator<<(std::ostream &os, const vector_t &v) { return os << v.x_ << ' ' << v.y_; }
  friend std::istream &operator>>(std::istream &is, vector_t &v) { return is >> v.x_ >> v.y_; }

  friend bool operator==(const vector_t &lhs, const vector_t &rhs) { return abs(lhs.x_ - rhs.x_) < EPS_ && abs(lhs.y_ - rhs.y_) < EPS_; }
  friend bool operator!=(const vector_t &lhs, const vector_t &rhs) { return !(lhs == rhs); }

  friend bool operator<(const vector_t &lhs, const vector_t &rhs) { return lhs.x_ < rhs.x_ || (abs(lhs.x_ - rhs.x_) < 1e-9 && lhs.y_ < rhs.y_); }
  friend bool operator>(const vector_t &lhs, const vector_t &rhs) { return rhs < lhs; }
  friend bool operator<=(const vector_t &lhs, const vector_t &rhs) { return !(rhs < lhs); }
  friend bool operator>=(const vector_t &lhs, const vector_t &rhs) { return !(lhs < rhs); }

  friend vector_t operator+(const vector_t &lhs, const vector_t &rhs) { return vector_t(lhs) += rhs; }
  friend vector_t operator-(const vector_t &lhs, const vector_t &rhs) { return vector_t(lhs) -= rhs; }
  friend vector_t operator*(const vector_t &lhs, T scalar) { return vector_t(lhs) *= scalar; }
  friend vector_t operator*(T scalar, const vector_t &rhs) { return vector_t(rhs) *= scalar; }
  friend vector_t operator/(const vector_t &lhs, T scalar) { return vector_t(lhs) /= scalar; }

private:
  T x_, y_;
};

using vec_t = vector_t<double>;
// clang-format on
