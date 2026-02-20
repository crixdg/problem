#include <bits/stdc++.h>
using namespace std;

string longestRepeatedSubstring(string &s) {
    int n = s.size();

    // Prefix Doubling
    vector<int> sa(n), rk(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rk[i] = s[i];
    }

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rk[a] != rk[b]) { return rk[a] < rk[b]; }
            int u = (a + k < n) ? rk[a + k] : -1;
            int v = (b + k < n) ? rk[b + k] : -1;
            return u < v;
        };

        sort(begin(sa), end(sa), cmp);
        vector<int> nrk(n);
        for (int i = 1; i < n; i++) {
            nrk[sa[i]] = nrk[sa[i - 1]] + int(cmp(sa[i - 1], sa[i]));
        }
        rk = nrk;
    }

    // Kasai's Algorithm
    for (int i = 0; i < n; i++) { rk[sa[i]] = i; }
    int mx = 0, mxi = 0;
    for (int i = 0, h = 0; i < n; i++) {
        if (rk[i] == 0) { continue; }
        int j = sa[rk[i] - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) { h++; }
        if (h > mx || h == mx && i < mx) { mx = h, mxi = i; }
        if (h > 0) { h--; }
    }
    return s.substr(mxi, mx);
}

int main() {
    string s("abckjdahcoasbekjcbabasdbababadbadbabdbcbaxbabadbadbaad");
    cout << longestRepeatedSubstring(s) << endl;
}
