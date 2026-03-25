/**
 *    author: crixdg
 *    modified: 25.03.2026 11:30:50
 *    created: 25.03.2026 11:30:50
 *    description: combinatorics class for small values
 *    notes:
 *    - precomputed Pascal's triangle; n <= 2000.
 *    - P is not supported.
 **/
#include <bits/stdc++.h>

/** combinatorics class for small values **/
// clang-format off
class combinatorics_small_t {
public:
  combinatorics_small_t() { build(0); }
  combinatorics_small_t(int n) { build(n); }

  void build(int n) {
    assert(n >= 0 && n <= 2000);
    c_.resize(n + 1, std::vector<long long>(n + 1));
    for (int i = 0; i <= n; i++) {
      c_[i][0] = c_[i][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        c_[i][j] = c_[i - 1][j] + c_[i - 1][j - 1];
      }
    }
    n_ = n;
  }

  void extend(int n) {
    assert(n >= 0 && n <= 2000);
    if (n <= n_) { return; }
    c_.resize(n + 1, std::vector<long long>(n + 1));
    for (int i = n_ + 1; i <= n; i++) {
      c_[i][0] = c_[i][i] = 1;
    }
    for (int i = n_ + 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        c_[i][j] = c_[i - 1][j] + c_[i - 1][j - 1];
      }
    }
    n_ = n;
  }

  long long C(int n, int k) {
    if (k < 0 || k > n) { return 0; }
    extend(n); return c_[n][k];
  }

  long long P(int n, int k) {
    throw std::invalid_argument("P is not supported for combinatorics_small_t");
  }

private:
  int n_; std::vector<std::vector<long long>> c_;
};

using comb_t = combinatorics_small_t;
// clang-format on
