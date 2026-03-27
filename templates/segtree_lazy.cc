/**
 *    author: crixdg
 *    modified: 26.03.2026 16:58:30
 *    created: 26.03.2026 16:58:30
 **/
#include <bits/stdc++.h>

using namespace std;

/**
 * V -> segment value type
 * F -> lazy tag type (function applied to segment)
 * e() -> identity value for V
 * id() -> identity tag for F (no pending updates)
 * op(a, b) -> merge two segment values
 * map(f, v, len) -> apply tag f to segment value v of length len
 * compose(f, g) -> tag equivalent to "first g, then f"
 **/
template <class A>
concept lazy_action_c = requires(typename A::V a, typename A::V b, typename A::F f, typename A::F g, int len) {
  typename A::V;
  typename A::F;
  A::e();
  A::id();
  A::op(a, b);
  A::map(f, a, len);
  A::compose(f, g);
};

/** lazy segment tree **/
template <lazy_action_c A>
class lazy_segtree_t {
public:
  using V = typename A::V;
  using F = typename A::F;

  /** construct a lazy segment tree of size n with fill value A::e() **/
  explicit lazy_segtree_t(int n, V fill = A::e()) : n_(n) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, A::e());
    lz_.assign(2 * sz_, A::id());
    has_.assign(2 * sz_, false);
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = fill; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  /** construct a lazy segment tree from a vector of values **/
  explicit lazy_segtree_t(const vector<V> &a) : n_((int)a.size()) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, A::e());
    lz_.assign(2 * sz_, A::id());
    has_.assign(2 * sz_, false);
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = a[i]; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  /** return the size of the lazy segment tree **/
  int size() const { return n_; }

  /** aggregate on [l, r) ; empty range -> identity */
  V query(int l, int r) {
    assert(0 <= l && l <= r && r <= n_);
    return query_(1, 0, sz_, l, r);
  }

  /** apply tag x to [l, r) */
  void apply(int l, int r, F x) {
    assert(0 <= l && l <= r && r <= n_);
    apply_(1, 0, sz_, l, r, x);
  }

  /** set the value at index i to t **/
  void set(int i, V t) {
    assert(0 <= i && i < n_);
    set_(1, 0, sz_, i, t);
  }

  /** return the aggregate of the entire segment tree **/
  V all() const {
    assert(n_ > 0);
    return tr_[1];
  }

private:
  int n_{}, sz_{};
  vector<V> tr_;
  vector<F> lz_;
  vector<bool> has_;

  /** pull up the value at index i **/
  void pull(int i) { tr_[i] = A::op(tr_[i << 1], tr_[i << 1 | 1]); }

  /** apply tag x to the segment at index i **/
  void apply_node(int i, int len, F x) {
    tr_[i] = A::map(x, tr_[i], len);
    if (has_[i]) {
      lz_[i] = A::compose(x, lz_[i]);
    } else {
      lz_[i] = x;
      has_[i] = true;
    }
  }

  /** push down the tag at index i **/
  void push(int i, int l, int r) {
    if (!has_[i] || r - l <= 1) { return; }
    int m = (l + r) >> 1;
    apply_node(i << 1, m - l, lz_[i]);
    apply_node(i << 1 | 1, r - m, lz_[i]);
    lz_[i] = A::id();
    has_[i] = false;
  }

  /** aggregate on [ql, qr) */
  V query_(int i, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) { return A::e(); }
    if (ql <= l && r <= qr) { return tr_[i]; }
    push(i, l, r);
    int m = (l + r) >> 1;
    return A::op(query_(i << 1, l, m, ql, qr), query_(i << 1 | 1, m, r, ql, qr));
  }

  /** apply tag x to [ql, qr) */
  void apply_(int i, int l, int r, int ql, int qr, F x) {
    if (qr <= l || r <= ql) { return; }
    if (ql <= l && r <= qr) {
      apply_node(i, r - l, x);
      return;
    }
    push(i, l, r);
    int m = (l + r) >> 1;
    apply_(i << 1, l, m, ql, qr, x);
    apply_(i << 1 | 1, m, r, ql, qr, x);
    pull(i);
  }

  void set_(int i, int l, int r, int p, V t) {
    if (r - l == 1) {
      tr_[i] = t;
      lz_[i] = A::id();
      has_[i] = false;
      return;
    }
    push(i, l, r);
    int m = (l + r) >> 1;
    if (p < m) {
      set_(i << 1, l, m, p, t);
    } else {
      set_(i << 1 | 1, m, r, p, t);
    }
    pull(i);
  }
};

/** lazy actions: example for add_sum, set_sum **/

struct lazy_add_sum_t {
  using V = long long;
  using F = long long;
  static V e() { return 0LL; }
  static F id() { return 0LL; }
  static V op(V a, V b) { return a + b; }
  static V map(F x, V t, int len) { return (x == id() ? t : t + x * len); }
  static F compose(F x, F y) { return (x == id() ? y : x + y); } // first y, then x
};
static_assert(lazy_action_c<lazy_add_sum_t>);

struct lazy_set_sum_t {
  using V = long long;
  using F = long long;
  static V e() { return 0LL; }
  static F id() { return 0LL; }
  static V op(V a, V b) { return a + b; }
  static V map(F x, V t, int len) { return (x == id() ? t : x * len); }
  static F compose(F x, F y) { return (x == id() ? y : x); } // first y, then x
};
static_assert(lazy_action_c<lazy_set_sum_t>);

using lazy_segtree_sum_t = lazy_segtree_t<lazy_add_sum_t>;
