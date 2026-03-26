/**
 *    author: crixdg
 *    modified: 26.03.2026 00:15:13
 *    created: 26.03.2026 00:15:13
 **/
#include <bits/stdc++.h>

/** kmp lps array **/
std::vector<int> kmp_lps(const std::string &s) {
  int n = s.size();
  std::vector<int> f(n, 0);
  for (int i = 1, j = 0; i < n; i++) {
    while (j > 0 && s[i] != s[j]) { j = f[j - 1]; }
    if (s[i] == s[j]) { j++; }
    f[i] = j;
  }
  return f;
}

/** z-array **/
std::vector<int> z_array(const std::string &s) {
  int n = s.size();
  std::vector<int> z(n, 0);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    if (i < r) { z[i] = std::min(z[i - l], r - i); }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) { z[i]++; }
    if (i + z[i] > r) { l = i, r = i + z[i]; }
  }
  z[0] = n;
  return z;
}
