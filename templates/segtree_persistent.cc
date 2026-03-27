/**
 *    author: crixdg
 *    timestamp: 28.03.2026 06:26:49
 **/

#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- PERSISTENT SEGMENT TREE ----------------------------- **/

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

/** persistent segment tree **/
template <monoid_c M>
struct persistent_segment_tree_t {
  using V = typename M::V;

  int n{};       // real_size
  int root0{-1}; // root of the initial array
  struct node_t {
    V val{};            // node value
    int lc{-1}, rc{-1}; // left and right child indices
  };
  vector<node_t> tr; // segment tree nodes

  /** tree on [0, n); a may be shorter (padded with e()) **/
  explicit persistent_segment_tree_t(int n, const vector<V> &a = {}) : n(n) {
    tr.clear();
    if (n == 0) {
      root0 = -1;
      return;
    }
    vector<V> b(a);
    b.resize(n, M::e());
    root0 = build(0, n, b);
  }

  /** new root after set position i to x **/
  int update(int ver, int i, V x) {
    assert(0 <= i && i < n && ver >= 0);
    return upd(ver, 0, n, i, x);
  }

  /** aggregate on [l, r); empty range -> e() **/
  V query(int ver, int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    if (l == r || ver < 0) { return M::e(); }
    return query_(ver, 0, n, l, r);
  }

  /** create a new node **/
  int new_node_(V v, int lc = -1, int rc = -1) {
    tr.push_back({v, lc, rc});
    return (int)tr.size() - 1;
  }

  /** build the segment tree from a vector of values **/
  int build_(int l, int r, const vector<V> &a) {
    if (r - l == 1) { return new_node_(a[l]); }
    int m = (l + r) >> 1;
    int L = build_(l, m, a);
    int R = build_(m, r, a);
    return new_node_(M::op(tr[L].val, tr[R].val), L, R);
  }

  /** update the segment tree at position i to x **/
  int update_(int v, int l, int r, int i, V x) {
    if (r - l == 1) { return new_node_(x); }
    int m = (l + r) >> 1;
    const node_t &nd = tr[v];
    if (i < m) {
      int nL = update_(nd.lc, l, m, i, x);
      return new_node_(M::op(tr[nL].val, tr[nd.rc].val), nL, nd.rc);
    }
    int nR = update_(nd.rc, m, r, i, x);
    return new_node_(M::op(tr[nd.lc].val, tr[nR].val), nd.lc, nR);
  }

  /** query the segment tree on [ql, qr) **/
  V query_(int v, int l, int r, int ql, int qr) const {
    if (qr <= l || r <= ql) { return M::e(); }
    if (ql <= l && r <= qr) { return tr[v].val; }
    int m = (l + r) >> 1;
    return M::op(query_(tr[v].lc, l, m, ql, qr), query_(tr[v].rc, m, r, ql, qr));
  }
};

/** ----------------------------- MONOIDS ----------------------------- **/

template <typename T = long long>
struct monoid_sum_t {
  using V = T;
  static V e() { return 0; }
  static V op(V a, V b) { return a + b; }
};
static_assert(monoid_c<monoid_sum_t<>>);

/** ----------------------------- PERSISTENT SEGMENT TREE TYPE ALIASES ----------------------------- **/

using persistent_segtree_t = persistent_segment_tree_t<monoid_sum_t<>>;
