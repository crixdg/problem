#include <bits/stdc++.h>
using namespace std;

void suffixArray(string s) {
    int n = s.size();
    vector<int> sa(n), rk(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rk[i] = s[i];
    }

    sort(begin(sa), end(sa), [&](int x, int y) { return rk[x] < rk[y]; });
    rk[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
        rk[sa[i]] = rk[sa[i - 1]] + int(s[sa[i]] != s[sa[i - 1]]);
    }

    for (int k = 1; k < n; k <<= 1) {
         

        vector<int> nrk(n);
        nrk[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            int t = 0;
            if (rk[sa[i]] != rk[sa[i - 1]]) {
                t = 1;
            } else {
                int u = sa[i] + k < n ? rk[sa[i] + k] : -1;
                int v = sa[i - 1] + k < n ? rk[sa[i - 1] + k] : -1;
                if (u != v) { t = 1; }
            }
            nrk[sa[i]] = nrk[sa[i - 1]] + t;
        }
        rk = nrk;
    }
}

int main() { return 0; }
