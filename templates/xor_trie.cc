/**
 *    author: crixdg
 *    timestamp: 28.03.2026 02:23:17
 **/

#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- BINARY TRIE (XOR / bit DP) ----------------------------- **/

/**
 * Values are interpreted in [0, 2^B). insert/remove maintain multiset counts.
 * max_xor(x): maximum (x ^ y) over inserted y (empty trie -> -1).
 **/
template <int B = 30>
  requires(B > 0 && B <= 63)
struct xor_trie_t {
  static constexpr uint64_t MASK = (1ULL << B) - 1;

  struct node_t {
    array<int, 2> nxt;
    int cnt = 0;
    node_t() { nxt.fill(-1); }
  };
  vector<node_t> tr;

  xor_trie_t() { tr.emplace_back(); }

  int new_node() {
    tr.emplace_back();
    return static_cast<int>(tr.size()) - 1;
  }

  void clear() {
    tr.clear();
    tr.emplace_back();
  }

  void insert(uint64_t x) {
    x &= MASK;
    int u = 0;
    tr[u].cnt++;
    for (int k = B - 1; k >= 0; k--) {
      int b = (x >> k) & 1;
      if (tr[u].nxt[b] == -1) { tr[u].nxt[b] = new_node(); }
      u = tr[u].nxt[b];
      tr[u].cnt++;
    }
  }

  bool erase(uint64_t x) {
    if (empty()) { return false; }
    x &= MASK;
    {
      int u = 0;
      for (int k = B - 1; k >= 0; k--) {
        int b = (x >> k) & 1;
        int v = tr[u].nxt[b];
        if (v == -1 || tr[v].cnt == 0) { return false; }
        u = v;
      }
    }
    {
      int u = 0;
      tr[u].cnt--;
      for (int k = B - 1; k >= 0; k--) {
        int b = (x >> k) & 1;
        int v = tr[u].nxt[b];
        tr[v].cnt--;
        u = v;
      }
    }
    return true;
  }

  int count(uint64_t x) const {
    x &= MASK;
    int u = 0;
    for (int k = B - 1; k >= 0; k--) {
      int b = (x >> k) & 1;
      if (tr[u].nxt[b] == -1) { return 0; }
      u = tr[u].nxt[b];
    }
    return tr[u].cnt;
  }

  bool empty() const { return tr[0].cnt == 0; }

  /** maximum x ^ y for y in multiset **/
  int64_t max_xor(uint64_t x) const {
    if (empty()) { return int64_t(-1); }
    x &= MASK;
    int u = 0;
    uint64_t res = 0;
    for (int k = B - 1; k >= 0; k--) {
      int want = 1 - ((x >> k) & 1);
      int has = tr[u].nxt[want];
      if (has != -1 && tr[has].cnt > 0) {
        res |= uint64_t(1) << k;
        u = has;
      } else {
        u = tr[u].nxt[1 - want];
      }
    }
    return static_cast<int64_t>(res);
  }

  /** minimum x ^ y for y in multiset **/
  int64_t min_xor(uint64_t x) const {
    if (empty()) { return int64_t(-1); }
    x &= MASK;
    int u = 0;
    uint64_t res = 0;
    for (int k = B - 1; k >= 0; k--) {
      int same = (x >> k) & 1;
      int has = tr[u].nxt[same];
      if (has != -1 && tr[has].cnt > 0) {
        u = has;
      } else {
        res |= uint64_t(1) << k;
        u = tr[u].nxt[1 - same];
      }
    }
    return static_cast<int64_t>(res);
  }
};

/** ----------------------------- XOR TRIE TYPE ALIASES ----------------------------- **/

using xor_trie_i_t = xor_trie_t<31>;
using xor_trie_ll_t = xor_trie_t<63>;
