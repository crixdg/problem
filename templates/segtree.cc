/**
 *    author: crixdg
 *    timestamp: 27.03.2026 03:00:32
 **/

#include <bits/stdc++.h>

using namespace std;

/**
 * T -> segment value type
 * e() -> identity value for T
 * op(a, b) -> merge two segment values
 **/
template <class M>
concept monoid_c = requires { typename M::V; } && requires(typename M::V a, typename M::V b) {
  M::e();
  M::op(a, b);
};

template <monoid_c M>
class segment_tree_t {
public:
  using V = typename M::V;

  /** construct a segment tree of size n with fill value M::e() **/
  explicit segment_tree_t(int n, V fill = M::e()) : n_(n) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, M::e());
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = fill; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  /** construct a segment tree from a vector of values **/
  explicit segment_tree_t(const vector<V> &a) : n_((int)a.size()) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, M::e());
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = a[i]; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  /** return the size of the segment tree **/
  int size() const { return n_; }

  /** set the value at index i to x **/
  void set(int i, V x) {
    assert(0 <= i && i < n_);
    for (i += sz_, tr_[i] = x; i >>= 1;) { pull(i); }
  }

  /** aggregate on [l, r) ; empty range -> identity */
  V query(int l, int r) const {
    assert(0 <= l && l <= r && r <= n_);
    if (l == r) { return M::e(); }
    V L = M::e(), R = M::e();
    for (l += sz_, r += sz_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) { L = M::op(L, tr_[l++]); }
      if (r & 1) { R = M::op(tr_[--r], R); }
    }
    return M::op(L, R);
  }

  /** return the aggregate of the entire segment tree **/
  V all() const {
    assert(n_ > 0);
    return tr_[1];
  }

private:
  int n_{}, sz_{};
  vector<V> tr_;

  /** pull up the value at index i **/
  void pull(int i) { tr_[i] = M::op(tr_[i << 1], tr_[i << 1 | 1]); }
};

/** monoids: example for sum, max, min **/
template <typename T = long long>
struct monoid_sum_t {
  using V = T;
  static V e() { return 0; }
  static V op(V a, V b) { return a + b; }
};

template <typename T>
struct monoid_max_t {
  using V = T;
  static V e() { return numeric_limits<V>::min(); }
  static V op(V a, V b) { return max(a, b); }
};

template <typename T>
struct monoid_min_t {
  using V = T;
  static V e() { return numeric_limits<V>::max(); }
  static V op(V a, V b) { return min(a, b); }
};

using segtree_t = segment_tree_t<monoid_sum_t<>>;

/** custom T : example for maximum segment tree **/
struct T_t {
  pair<int, int> pr;

  T_t() : pr(0, 0) {}
  T_t(int a, int b) : pr(a, b) {}
  T_t(pair<int, int> p) : pr(p) {}
  T_t(const T_t &other) : pr(other.pr) {}

  friend bool operator<(const T_t &a, const T_t &b) {
    return a.pr < b.pr;
  }
};

namespace std {
template <>
struct numeric_limits<T_t> {
  static T_t max() {
    return T_t{numeric_limits<int>::max(), numeric_limits<int>::max()};
  }
};
} // namespace std

using segtree_t_t = segment_tree_t<monoid_max_t<T_t>>;
