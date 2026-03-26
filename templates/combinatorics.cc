/**
 *    author: crixdg
 *    timestamp: 26.03.2026 17:25:56
 **/

#include <bits/stdc++.h>

using namespace std;

/** combinatorics class for small values **/
// clang-format off
class combinatorics_small_t {
public:
  combinatorics_small_t() {}
  combinatorics_small_t(int n) { extend(n); }

  void extend(int n) {
    assert(n >= 0 && n <= 2000);
    if (n <= n_) { return; }
    c_.resize(n + 1, vector<long long>(n + 1));
    for (int i = n_ + 1; i <= n; i++) { c_[i][0] = c_[i][i] = 1; }
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

private:
  int n_{0};
  vector<vector<long long>> c_{1, vector<long long>(1, 1)};
};

using comb_t = combinatorics_small_t;
// clang-format on
