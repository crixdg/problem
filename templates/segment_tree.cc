#include <bits/stdc++.h>

using namespace std;

// Monoid: typename T, static T e(), static T op(T, T)
template <class M>
class segment_tree_t {
public:
  using T = typename M::T;

  /** single value `fill` on [0, n) */
  explicit segment_tree_t(int n, T fill = M::e()) : n_(n) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    d_.assign(2 * sz_, M::e());
    for (int i = 0; i < n_; ++i) { d_[sz_ + i] = fill; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  explicit segment_tree_t(const vector<T> &a) : n_((int)a.size()) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    d_.assign(2 * sz_, M::e());
    for (int i = 0; i < n_; ++i) { d_[sz_ + i] = a[i]; }
    for (int i = n_; i < sz_; ++i) { d_[sz_ + i] = M::e(); }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  int size() const { return n_; }

  void set(int i, T x) {
    assert(0 <= i && i < n_);
    for (i += sz_, d_[i] = x; i >>= 1;) { pull(i); }
  }

  /** aggregate on [l, r) ; empty range -> identity */
  T query(int l, int r) const {
    assert(0 <= l && l <= r && r <= n_);
    if (l == r) { return M::e(); }
    T L = M::e(), R = M::e();
    l += sz_;
    r += sz_;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) { L = M::op(L, d_[l++]); }
      if (r & 1) { R = M::op(d_[--r], R); }
    }
    return M::op(L, R);
  }

  T whole() const {
    assert(n_ > 0);
    return d_[1];
  }

private:
  int n_{}, sz_{};
  vector<T> d_;

  void pull(int i) { d_[i] = M::op(d_[i << 1], d_[i << 1 | 1]); }
};

// ---------- example monoids ----------

template <typename U = long long>
struct segtree_sum {
  using T = U;
  static T e() { return 0; }
  static T op(T a, T b) { return a + b; }
};

template <typename U>
struct segtree_max {
  using T = U;
  static T e() { return numeric_limits<T>::min(); }
  static T op(T a, T b) { return max(a, b); }
};

template <typename U>
struct segtree_min {
  using T = U;
  static T e() { return numeric_limits<T>::max(); }
  static T op(T a, T b) { return min(a, b); }
};

// e.g. segment_tree_t<segtree_sum<>> seg(n);
// e.g. segment_tree_t<segtree_max<int>> seg(a);
