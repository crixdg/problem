#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct matrix_t {
  int n{}, m{};
  vector<vector<T>> a;

  matrix_t() = default;
  matrix_t(int n_, int m_, T fill = T{}) : n(n_), m(m_), a(n_, vector<T>(m_, fill)) {}

  static matrix_t zeros(int n_, int m_) { return matrix_t(n_, m_, T(0)); }

  static matrix_t eye(int n_) {
    matrix_t r(n_, n_, T(0));
    for (int i = 0; i < n_; ++i) { r.a[i][i] = T(1); }
    return r;
  }

  const vector<T> &operator[](int i) const { return a[i]; }
  vector<T> &operator[](int i) { return a[i]; }

  matrix_t &operator+=(const matrix_t &o) {
    assert(n == o.n && m == o.m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) { a[i][j] += o.a[i][j]; }
    }
    return *this;
  }
  matrix_t operator+(const matrix_t &o) const {
    matrix_t r = *this;
    r += o;
    return r;
  }

  matrix_t operator*(const matrix_t &o) const {
    assert(m == o.n);
    matrix_t r(n, o.m, T(0));
    for (int i = 0; i < n; ++i) {
      for (int k = 0; k < m; ++k) {
        const T aik = a[i][k];
        if (aik == T(0)) { continue; }
        for (int j = 0; j < o.m; ++j) { r.a[i][j] += aik * o.a[k][j]; }
      }
    }
    return r;
  }

  /** square matrix only */
  matrix_t mpow(unsigned long long e) const {
    assert(n == m);
    matrix_t r = eye(n), b = *this;
    while (e) {
      if (e & 1) { r = r * b; }
      b = b * b;
      e >>= 1;
    }
    return r;
  }

  vector<T> apply(const vector<T> &v) const {
    assert((int)v.size() == m);
    vector<T> out(n, T(0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) { out[i] += a[i][j] * v[j]; }
    }
    return out;
  }
};
