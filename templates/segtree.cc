/**
 *    author: crixdg
 *    timestamp: 28.03.2026 03:13:12
 **/

#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- SEGMENT TREE ----------------------------- **/

/**
 * V -> segment value type
 * e() -> identity value for V
 * op(a, b) -> merge two segment values
 **/
template <class M>
concept monoid_c = requires { typename M::V; } && requires(typename M::V a, typename M::V b) {
  M::e();
  M::op(a, b);
};

template <monoid_c M>
struct segment_tree_t {
  using V = typename M::V;

  int n{}, sz{}; // real_size and segment tree array size
  vector<V> tr;  // segment tree values

  /** pull up the value at index i **/
  void pull_(int i) { tr[i] = M::op(tr[i << 1], tr[i << 1 | 1]); }

  /** construct a segment tree of size n with fill value M::e() **/
  explicit segment_tree_t(int n, V fill = M::e()) : n(n) {
    if (n == 0) { return; }
    for (sz = 1; sz < n; sz <<= 1) {}
    tr.assign(2 * sz, M::e());
    for (int i = 0; i < n; ++i) { tr[sz + i] = fill; }
    for (int i = sz - 1; i >= 1; --i) { pull_(i); }
  }

  /** construct a segment tree from a vector of values **/
  explicit segment_tree_t(const vector<V> &a) : n((int)a.size()) {
    if (n == 0) { return; }
    for (sz = 1; sz < n; sz <<= 1) {}
    tr.assign(2 * sz, M::e());
    for (int i = 0; i < n; ++i) { tr[sz + i] = a[i]; }
    for (int i = sz - 1; i >= 1; --i) { pull_(i); }
  }

  /** set the value at index i to x **/
  void set(int i, V x) {
    assert(0 <= i && i < n);
    for (i += sz, tr[i] = x; i >>= 1;) { pull_(i); }
  }

  /** aggregate on [l, r) ; empty range -> identity */
  V query(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) { return M::e(); }
    V L = M::e(), R = M::e();
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      if (l & 1) { L = M::op(L, tr[l++]); }
      if (r & 1) { R = M::op(tr[--r], R); }
    }
    return M::op(L, R);
  }

  /** return the aggregate of the entire segment tree **/
  V all() const {
    assert(n > 0);
    return tr[1];
  }
};

/** ----------------------------- MONOIDS ----------------------------- **/

/**
 * *SUM* MONOID
 **/
template <typename T = long long>
struct monoid_sum_t {
  using V = T;
  static V e() { return 0; }
  static V op(V a, V b) { return a + b; }
};
static_assert(monoid_c<monoid_sum_t<>>);

/**
 * *MAX* MONOID
 **/
template <typename T>
struct monoid_max_t {
  using V = T;
  static V e() { return numeric_limits<V>::min(); }
  static V op(V a, V b) { return max(a, b); }
};
static_assert(monoid_c<monoid_max_t<int>>);

/**
 * *MIN* MONOID
 **/
template <typename T>
struct monoid_min_t {
  using V = T;
  static V e() { return numeric_limits<V>::max(); }
  static V op(V a, V b) { return min(a, b); }
};
static_assert(monoid_c<monoid_min_t<int>>);

/** ----------------------------- SEGMENT TREE TYPE ALIASES ----------------------------- **/

using segtree_t = segment_tree_t<monoid_sum_t<>>;

/** ----------------------------- CUSTOM MONOID ----------------------------- **/

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
