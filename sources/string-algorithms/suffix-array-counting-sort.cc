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
    rk[sa[0]] = 1; // shift all rank +1 to get rid of conflicting 0
    for (int i = 1; i < n; i++) {
        rk[sa[i]] = rk[sa[i - 1]] + int(s[sa[i]] != s[sa[i - 1]]);
    }

    for (int k = 1; k < n; k <<= 1) {
        auto counting_sort = [&](int j) {
            vector<int> cnt(n + 1);
            for (int i = 0; i < n; i++) {
                int d = sa[i] + j < n ? rk[sa[i] + j] : 0;
                cnt[d]++;
            }
            for (int i = 1; i <= n; i++) { cnt[i] += cnt[i - 1]; }
            vector<int> ans(n);
            for (int i = n - 1; i >= 0; i--) {
                int d = sa[i] + j < n ? rk[sa[i] + j] : 0;
                ans[cnt[d] - 1] = sa[i];
                cnt[d]--;
            }
            sa = ans;
        };
        counting_sort(k);
        counting_sort(0);

        vector<int> nrk(n);
        nrk[sa[0]] = 1;
        for (int i = 1; i < n; i++) {
            int t = 0;
            if (rk[sa[i]] != rk[sa[i - 1]]) {
                t = 1;
            } else {
                int u = sa[i] + k < n ? rk[sa[i] + k] : 0;
                int v = sa[i - 1] + k < n ? rk[sa[i - 1] + k] : 0;
                if (u != v) { t = 1; }
            }
            nrk[sa[i]] = nrk[sa[i - 1]] + t;
        }
        rk = nrk;
        if (rk[sa[n - 1]] == n) { break; }
    }
}

int main() { return 0; }
