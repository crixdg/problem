#include <bits/stdc++.h>

std::vector<int> kmp_lps(const std::string &s) {
  int n = s.size();
  std::vector<int> f(n);
  for (int i = 1, j = 0; i < n; i++) {
    while (j > 0 && s[i] != s[j]) {
      j = f[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    f[i] = j;
  }
  return f;
}
