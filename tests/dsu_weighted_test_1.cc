/**https://judge.yosupo.jp/problem/unionfind_with_potential **/
/** verified find, unite, and diff operations **/
#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- WEIGHTED DISJOINT SET UNION ----------------------------- **/

template <typename Op>
concept weighted_dsu_op_c = requires { typename Op::W; } &&
                            requires(typename Op::W, typename Op::W a, typename Op::W b, typename Op::W d) {
                              Op::e();
                              Op::join(a, b);
                              Op::diff(a, b);
                              Op::flip(d);
                            };

/** weighted disjoint set union **/
template <weighted_dsu_op_c Op>
struct weighted_dsu_t {
  using W = typename Op::W;

  int comp_sz;
  vector<int> p, sz;
  vector<W> w;

  explicit weighted_dsu_t(int n) : comp_sz(n), p(n), w(n, Op::e()), sz(n, 1) {
    iota(p.begin(), p.end(), 0);
  }

  /** find root: full path compression **/
  pair<int, W> find(int x) {
    if (p[x] == x) { return {x, Op::e()}; }
    auto [r, dw] = find(p[x]);
    w[x] = Op::join(w[x], dw);
    p[x] = r;
    return {r, w[x]};
  }

  /** constraint diff(wx, wy) == d; false if contradictory **/
  bool unite(int x, int y, W d) {
    auto [fx, wx] = find(x);
    auto [fy, wy] = find(y);
    if (fx == fy) { return Op::diff(wx, wy) == d; }
    if (sz[fx] < sz[fy]) {
      swap(fx, fy);
      swap(wx, wy);
      d = Op::flip(d);
    }
    p[fy] = fx;
    w[fy] = Op::diff(Op::diff(wx, wy), d);
    sz[fx] += sz[fy];
    comp_sz--;
    return true;
  }

  /** check if two elements are in the same set **/
  bool same(int x, int y) { return find(x).first == find(y).first; }

  /** return the potential of x **/
  W potential(int x) { return find(x).second; }

  /** return the difference between the potential of x and y **/
  optional<W> diff(int x, int y) {
    auto [fx, wx] = find(x);
    auto [fy, wy] = find(y);
    if (fx != fy) { return nullopt; }
    return Op::diff(wx, wy);
  }

  /** return the size of the set containing x **/
  int size(int x) { return sz[find(x).first]; }

  /** return the number of connected components **/
  int components() { return comp_sz; }
};

/** ----------------------------- WEIGHTED DSU OPERATIONS ----------------------------- **/

/**
 * * LABEL(x) - LABEL(y) = d
 **/
template <class T = long long>
struct dsu_weight_op_1 {
  using W = T;
  static W e() { return W(0); }
  static W join(W a, W b) { return a + b; }
  static W diff(W a, W b) { return a - b; }
  static W flip(W d) { return -d; }
};
static_assert(weighted_dsu_op_c<dsu_weight_op_1<long long>>);

/**
 * * LABEL(x) ^ LABEL(y) = d
 **/
struct dsu_weight_op_2 {
  using W = long long;
  static W e() { return W(0); }
  static W join(W a, W b) { return a ^ b; }
  static W diff(W a, W b) { return a ^ b; }
  static W flip(W d) { return d; }
};
static_assert(weighted_dsu_op_c<dsu_weight_op_2>);

/**
 * * LABEL(x) - LABEL(y) = d (mod m)
 **/
template <class T = long long, T M_ = T(1e9 + 7)>
struct dsu_weight_op_3 {
  using W = T;
  static W e() { return W(0); }
  static W join(W a, W b) { return (a + b) % M_; }
  static W diff(W a, W b) {
    W ans = (a - b) % M_;
    return (ans < 0 ? ans + M_ : ans);
  }
  static W flip(W d) {
    W ans = -d % M_;
    return (ans < 0 ? ans + M_ : ans);
  }
};
static_assert(weighted_dsu_op_c<dsu_weight_op_3<long long, (long long)1e9 + 7>>);

/** ----------------------------- WEIGHTED DSU TYPE ALIAS ----------------------------- **/

using w_dsu_t = weighted_dsu_t<dsu_weight_op_3<long long, 998244353>>;

/** --------------------------------- MAIN --------------------------------- **/

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) ((void)0)
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  w_dsu_t dsu(n);
  {
    while (q--) {
      int op;
      cin >> op;
      if (op == 0) {
        int u, v, x;
        cin >> u >> v >> x;
        cout << int(dsu.unite(u, v, x)) << '\n';
      } else {
        int u, v;
        cin >> u >> v;
        auto ans = dsu.diff(u, v);
        if (ans.has_value()) {
          cout << ans.value() << '\n';
        } else {
          cout << -1 << '\n';
        }
      }
    }
  }
  return 0;
}
