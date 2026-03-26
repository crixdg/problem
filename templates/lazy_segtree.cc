/**
 *    author: crixdg
 *    modified: 26.03.2026 16:58:30
 *    created: 26.03.2026 16:58:30
 **/
#include <bits/stdc++.h>

using namespace std;

/**
 * V_ -> segment value type
 * T_ -> lazy tag type
 * e() -> identity value for V_
 * x() -> identity tag for T_
 * op(a, b) -> merge two segment values
 * map(f, v, len) -> apply tag f to segment value v of length len
 * compose(f, g) -> tag equivalent to "first g, then f"
 **/
template <class A>
concept lazy_action_c = requires(typename A::V_ a, typename A::V_ b, typename A::T_ f, typename A::T_ g, int len) {
  typename A::V_;
  typename A::T_;
  A::e();
  A::x();
  A::op(a, b);
  A::map(f, a, len);
  A::compose(f, g);
};

template <lazy_action_c A>
class lazy_segtree_t {
public:
  using V_ = typename A::V_;
  using T_ = typename A::T_;

  explicit lazy_segtree_t(int n, V_ fill = A::e()) : n_(n) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, A::e());
    lz_.assign(2 * sz_, A::x());
    has_.assign(2 * sz_, false);
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = fill; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  explicit lazy_segtree_t(const vector<V_> &a) : n_((int)a.size()) {
    if (n_ == 0) { return; }
    for (sz_ = 1; sz_ < n_; sz_ <<= 1) {}
    tr_.assign(2 * sz_, A::e());
    lz_.assign(2 * sz_, A::x());
    has_.assign(2 * sz_, false);
    for (int i = 0; i < n_; ++i) { tr_[sz_ + i] = a[i]; }
    for (int i = sz_ - 1; i >= 1; --i) { pull(i); }
  }

  int size() const { return n_; }

  /** aggregate on [l, r) */
  V_ query(int l, int r) {
    assert(0 <= l && l <= r && r <= n_);
    return query_(1, 0, sz_, l, r);
  }

  /** apply tag x to [l, r) */
  void apply(int l, int r, T_ x) {
    assert(0 <= l && l <= r && r <= n_);
    apply_(1, 0, sz_, l, r, x);
  }

  void set(int i, V_ t) {
    assert(0 <= i && i < n_);
    set_(1, 0, sz_, i, t);
  }

  V_ all() const {
    assert(n_ > 0);
    return tr_[1];
  }

private:
  int n_{}, sz_{};
  vector<V_> tr_;
  vector<T_> lz_;
  vector<bool> has_;

  void pull(int i) { tr_[i] = A::op(tr_[i << 1], tr_[i << 1 | 1]); }

  void apply_node(int i, int len, T_ x) {
    tr_[i] = A::map(x, tr_[i], len);
    if (has_[i]) {
      lz_[i] = A::compose(x, lz_[i]);
    } else {
      lz_[i] = x;
      has_[i] = true;
    }
  }

  void push(int i, int l, int r) {
    if (!has_[i] || r - l <= 1) { return; }
    int m = (l + r) >> 1;
    apply_node(i << 1, m - l, lz_[i]);
    apply_node(i << 1 | 1, r - m, lz_[i]);
    lz_[i] = A::x();
    has_[i] = false;
  }

  /** aggregate on [ql, qr) */
  V_ query_(int i, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) { return A::e(); }
    if (ql <= l && r <= qr) { return tr_[i]; }
    push(i, l, r);
    int m = (l + r) >> 1;
    return A::op(query_(i << 1, l, m, ql, qr), query_(i << 1 | 1, m, r, ql, qr));
  }

  /** apply tag x to [ql, qr) */
  void apply_(int i, int l, int r, int ql, int qr, T_ x) {
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

  void set_(int i, int l, int r, int p, V_ t) {
    if (r - l == 1) {
      tr_[i] = t;
      lz_[i] = A::x();
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
  using V_ = long long;
  using T_ = long long;
  static V_ e() { return 0LL; }
  static T_ x() { return 0LL; }
  static V_ op(V_ a, V_ b) { return a + b; }
  static V_ map(T_ x, V_ t, int len) { return t + x * len; }
  static T_ compose(T_ x, T_ y) { return x + y; } // first y, then x
};

struct lazy_set_sum_t {
  using V_ = long long;
  using T_ = long long;
  static V_ e() { return 0LL; }
  static T_ x() { return 0LL; }
  static V_ op(V_ a, V_ b) { return a + b; }
  static V_ map(T_ x, V_ t, int len) { return x * len; }
  static T_ compose(T_ x, T_ y) { return x; } // first y, then x
};

using lazy_segtree_sum_t = lazy_segtree_t<lazy_add_sum_t>;
