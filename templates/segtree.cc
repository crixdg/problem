/**
 *    author: crixdg
 *    modified: 26.03.2026 16:09:26
 *    created: 26.03.2026 15:47:54
 **/
#include <bits/stdc++.h>

using namespace std;

/**
 * T -> segment value type
 * e() -> identity value for T
 * op(a, b) -> merge two segment values
 **/
template <class M>
concept monoid_c = requires { typename M::T; } && requires(typename M::T a, typename M::T b) {
  M::e();
  M::op(a, b);
};

template <monoid_c M>
class segment_tree_t {
public:
  using T = typename M::T;

  explicit segment_tree_t(int n, T fill = M::e()) : n_(n) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, M::e());
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = fill; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  explicit segment_tree_t(const vector<T> &a) : n_((int)a.size()) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, M::e());
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = a[i]; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  int size() const { return n_; }

  void set(int i, T x) {
    assert(0 <= i && i < n_);
    for (i += sz_, tr_[i] = x; i >>= 1;) { pull(i); }
  }

  /** aggregate on [l, r) ; empty range -> identity */
  T query(int l, int r) const {
    assert(0 <= l && l <= r && r <= n_);
    if (l == r) { return M::e(); }
    T L = M::e(), R = M::e();
    for (l += sz_, r += sz_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) { L = M::op(L, tr_[l++]); }
      if (r & 1) { R = M::op(tr_[--r], R); }
    }
    return M::op(L, R);
  }

  T all() const {
    assert(n_ > 0);
    return tr_[1];
  }

private:
  int n_{}, sz_{};
  vector<T> tr_;

  void pull(int i) { tr_[i] = M::op(tr_[i << 1], tr_[i << 1 | 1]); }
};

/** monoids: example for sum, max, min **/
template <typename U = long long>
struct monoid_sum_t {
  using T = U;
  static T e() { return 0; }
  static T op(T a, T b) { return a + b; }
};

template <typename U>
struct monoid_max_t {
  using T = U;
  static T e() { return numeric_limits<T>::min(); }
  static T op(T a, T b) { return max(a, b); }
};

template <typename U>
struct monoid_min_t {
  using T = U;
  static T e() { return numeric_limits<T>::max(); }
  static T op(T a, T b) { return min(a, b); }
};

using segtree_t = segment_tree_t<monoid_sum_t<>>;
// clang-format on

/** custom U : example for maximum segment tree **/
//clang-format off
struct U_t {
  pair<int, int> pr;

  U_t() : pr(0, 0) {}
  U_t(int a, int b) : pr(a, b) {}
  U_t(pair<int, int> p) : pr(p) {}
  U_t(const U_t &other) : pr(other.pr) {}

  friend bool operator<(const U_t &a, const U_t &b) {
    return a.pr < b.pr;
  }
};

namespace std {
template <>
struct numeric_limits<U_t> {
  static U_t max() {
    return U_t{numeric_limits<int>::max(), numeric_limits<int>::max()};
  }
};
} // namespace std

using segtree_u_t = segment_tree_t<monoid_max_t<U_t>>;
// clang-format on
