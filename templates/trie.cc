/**
 *    author: crixdg
 *    timestamp: 28.03.2026 02:05:26
 **/

#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- STRING TRIE (pool nodes) ----------------------------- **/

template <int SIGMA = 26, char BASE = 'a'>
struct trie_t {
  struct node_t {
    array<int, SIGMA> nxt;
    int pass = 0;
    int end = 0;
    node_t() { nxt.fill(-1); }
  };
  vector<node_t> tr;

  trie_t() { tr.emplace_back(); }

  static int ord(char c) {
    assert(BASE <= c && c < BASE + SIGMA);
    return static_cast<unsigned char>(c) - static_cast<unsigned char>(BASE);
  }

  int new_node() {
    tr.emplace_back();
    return static_cast<int>(tr.size()) - 1;
  }

  void clear() {
    tr.clear();
    tr.emplace_back();
  }

  void insert(const string &s) {
    int u = 0;
    tr[u].pass++;
    for (char ch : s) {
      int o = ord(ch);
      if (tr[u].nxt[o] == -1) { tr[u].nxt[o] = new_node(); }
      u = tr[u].nxt[o];
      tr[u].pass++;
    }
    tr[u].end++;
  }

  /** remove one occurrence of s; false if none **/
  bool erase(const string &s) {
    {
      int u = 0;
      for (char ch : s) {
        int o = ord(ch);
        if (tr[u].nxt[o] == -1) { return false; }
        u = tr[u].nxt[o];
      }
      if (tr[u].end == 0) { return false; }
    }
    {
      int u = 0;
      tr[u].pass--;
      for (char ch : s) {
        int o = ord(ch);
        int v = tr[u].nxt[o];
        tr[v].pass--;
        u = v;
      }
      tr[u].end--;
    }
    return true;
  }

  /** # strings with prefix s **/
  int count_prefix(const string &s) const {
    int u = 0;
    for (char ch : s) {
      int o = ord(ch);
      if (tr[u].nxt[o] == -1) { return 0; }
      u = tr[u].nxt[o];
    }
    return tr[u].pass;
  }

  /** # occurrences of exact string s **/
  int count_exact(const string &s) const {
    int u = 0;
    for (char ch : s) {
      int o = ord(ch);
      if (tr[u].nxt[o] == -1) { return 0; }
      u = tr[u].nxt[o];
    }
    return tr[u].end;
  }

  bool contains(const string &s) const { return count_exact(s) > 0; }

  /** longest prefix of s that exists as a prefix of some inserted string **/
  int longest_prefix_match(const string &s) const {
    int u = 0, len = 0;
    for (char ch : s) {
      int o = ord(ch);
      if (tr[u].nxt[o] == -1) { break; }
      u = tr[u].nxt[o];
      len++;
    }
    return len;
  }
};

/** ----------------------------- TRIE TYPE ALIASES ----------------------------- **/

using trie_lower_t = trie_t<26, 'a'>;
using trie_digit_t = trie_t<10, '0'>;
using trie_bool_t = trie_t<2, '0'>;
