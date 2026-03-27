#include <bits/stdc++.h>

using namespace std;

// ----------------------------- MATRIX -----------------------------

/** supports up to 4x4 matrices */
template <typename T, int N, int M>
  requires(integral<T> || floating_point<T>) && (N >= 1 && N <= 4) && (M >= 1 && M <= 4)
struct matrix_t {
  T a[N][M];

  matrix_t() : matrix_t(T{}) {}
  matrix_t(T fill = T{}) { fill(begin(a), end(a), fill); }
  matrix_t(const vector<vector<T>> &a) : matrix_t(a.data()) {}
  matrix_t(const T a[N][M]) : matrix_t(a, end(a)) {}
  matrix_t(const T *a, const T *end) { copy(a, end, begin(a)); }

  static matrix_t zeros(int n, int m) { return matrix_t(n, m); }
  static matrix_t identity(int n) {
    matrix_t r(n, n);
    for (int i = 0; i < n; ++i) { r.a[i][i] = T(1); }
    return r;
  }

  T &at(int r, int c) { return a[r][c]; }
  const T &at(int r, int c) const { return a[r][c]; }

  // arithmetic operations
  template <int O_N, int O_M>
    requires(O_N == N && O_M == M)
  matrix_t &operator+=(const matrix_t<T, O_N, O_M> &o) {
    transform(begin(a), end(a), begin(o.a), begin(a), plus<T>());
    return *this;
  }

  template <int O_N, int O_M>
    requires(O_N == N && O_M == M)
  matrix_t &operator-=(const matrix_t<T, O_N, O_M> &o) {
    transform(begin(a), end(a), begin(o.a), begin(a), minus<T>());
    return *this;
  }

  template <int O_N, int O_M>
    requires(O_M == N)
  matrix_t &operator*=(const matrix_t<T, O_N, O_M> &o) {
    matrix_t<T, N, O_M> r;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < O_M; ++j) {
        T sum = T{};
        for (int k = 0; k < M; ++k) { sum += a[i][k] * o.a[k][j]; }
        r.a[i][j] = sum;
      }
    }
    *this = r;
    return *this;
  }

  friend matrix_t operator+(const matrix_t &a, const matrix_t &b) { return matrix_t<T, N, M>(a) += b; }
  friend matrix_t operator-(const matrix_t &a, const matrix_t &b) { return matrix_t<T, N, M>(a) -= b; }
  template <int O_N, int O_M>
    requires(O_M == N)
  friend matrix_t operator*(const matrix_t &a, const matrix_t<T, O_N, O_M> &b) { return matrix_t<T, N, O_M>(a) *= b; }

  matrix_t operator*(T scalar) const {
    matrix_t<T, N, M> r(*this);
    transform(begin(r.a), end(r.a), begin(r.a), [&](T &x) { return x * scalar; });
    return *this;
  }

  T det() const {
    if (N == 1) { return a[0][0]; }
    if (N == 2) { return a[0][0] * a[1][1] - a[0][1] * a[1][0]; }
    if (N == 3) {
      T a00 = a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1]);
      T a01 = a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0]);
      T a02 = a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);
      return a00 - a01 + a02;
    }

    // row == 4
    const T &a00 = a[0][0], &a01 = a[0][1], &a02 = a[0][2], &a03 = a[0][3];
    const T &a10 = a[1][0], &a11 = a[1][1], &a12 = a[1][2], &a13 = a[1][3];
    const T &a20 = a[2][0], &a21 = a[2][1], &a22 = a[2][2], &a23 = a[2][3];
    const T &a30 = a[3][0], &a31 = a[3][1], &a32 = a[3][2], &a33 = a[3][3];

    T m0 = a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 * a31);
    T m1 = a10 * (a22 * a33 - a23 * a32) - a12 * (a20 * a33 - a23 * a30) + a13 * (a20 * a32 - a22 * a30);
    T m2 = a10 * (a21 * a33 - a23 * a31) - a11 * (a20 * a33 - a23 * a30) + a13 * (a20 * a31 - a21 * a30);
    T m3 = a10 * (a21 * a32 - a22 * a31) - a11 * (a20 * a32 - a22 * a30) + a12 * (a20 * a31 - a21 * a30);
    return a00 * m0 - a01 * m1 + a02 * m2 - a03 * m3;
  }

  matrix_t transpose() const {
    matrix_t<T, M, N> r;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) { r.a[j][i] = a[i][j]; }
    }
    return r;
  }

  matrix_t inverse() const {
    T d = det();
    assert(d != T(0));
    matrix_t<T, N, N> r;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) { r.a[i][j] = a[j][i]; }
    }
    return r;
  }

  T trace() const {
    T sum = T{};
    for (int i = 0; i < N; ++i) { sum += a[i][i]; }
    return sum;
  }

  int rank() const {
    int r = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (a[i][j] != T(0)) {
          r++;
          break;
        }
      }
    }
    return r;
  }
};
