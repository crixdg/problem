#include <bits/stdc++.h>
using namespace std;

void patternMatching(string &s, string &p) {
    int n = s.size(), m = p.size();
    int mod = 1e9 + 7;

    int h = 0;
    for (int i = 0; i < m; i++) {
        h = (1LL * h * 26 % mod + (p[i] - 'a' + 1)) % mod;
    }

    vector<int> bs(n + 1, 1);
    vector<int> hs(n + 1, 1);
    for (int i = 0; i < n; i++) {
        bs[i + 1] = 1LL * bs[i] * 26 % mod;
        hs[i + 1] = (1LL * hs[i] * 26 + (s[i] - 'a' + 1)) % mod;
    }

    for (int i = 0; i + m <= n; i++) {
        int t = (hs[i + m] - 1LL * hs[i] * bs[m] % mod) % mod;
        if (t < 0) { t = (t + mod) % mod; }
        if (t == h) { cout << i << ' '; }
    }
    cout << '\n';
}

int main() {
    string s("abcbdbcbcbwab");
    string p("bcb");
    patternMatching(s, p);
    return 0;
}
