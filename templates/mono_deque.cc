/**
 *    author: crixdg
 *    timestamp: 28.03.2026 03:37:40
 **/

#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- MONOTONIC DEQUE (sliding window min / max) ----------------------------- **/

template <typename T, typename Compare = less<T>>
struct monotonic_deque_t {
  deque<pair<int, T>> dq;
  Compare cmp;

  void clear() { dq.clear(); }

  bool empty() const { return dq.empty(); }

  /** drop positions strictly before L **/
  void pop_stale(int L) {
    while (!dq.empty() && dq.front().first < L) { dq.pop_front(); }
  }

  /** append (i, x); i should be >= previous i **/
  void push(int i, T x) {
    while (!dq.empty() && !cmp(dq.back().second, x)) { dq.pop_back(); }
    dq.emplace_back(i, x);
  }

  pair<int, T> front() const {
    assert(!empty());
    return dq.front();
  }

  pair<int, T> back() const {
    assert(!empty());
    return dq.back();
  }

  void pop_front() {
    assert(!empty());
    dq.pop_front();
  }

  void pop_back() {
    assert(!empty());
    dq.pop_back();
  }
};

template <typename T, typename Compare = less<T>>
using mq_t = monotonic_deque_t<T, Compare>;
