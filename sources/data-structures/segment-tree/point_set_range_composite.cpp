#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int mod = 998244353;

    int n, q;
    cin >> n >> q;
    vector<pair<long long, long long>> pr(2 * n);
    for (int i = 0; i < n; i++) { cin >> pr[i + n].first >> pr[i + n].second; }
    for (int i = 0; i < n; i++) {
        int j = i + n;
        for (; j > 1; j >>= 1) {
            if (j & 1) {
                pr[j >> 1].second =
                        (pr[j].first * pr[j ^ 1].second + pr[j].second) % mod;
            } else {
                pr[j >> 1].second =
                        (pr[j ^ 1].first * pr[j].second + pr[j ^ 1].second) %
                        mod;
            }
            pr[j >> 1].first = (pr[j].first * pr[j ^ 1].first) % mod;
        }
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int i, c, d;
            cin >> i >> c >> d;
            int j = i + n;
            pr[j] = {c, d};
            for (; j > 1; j >>= 1) {
                if (j & 1) {
                    pr[j >> 1].second =
                            (pr[j].first * pr[j ^ 1].second + pr[j].second) %
                            mod;
                } else {
                    pr[j >> 1].second = (pr[j ^ 1].first * pr[j].second +
                                         pr[j ^ 1].second) %
                                        mod;
                }
                pr[j >> 1].first = (pr[j].first * pr[j ^ 1].first) % mod;
            }
        } else {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            r--;
            long long a = 1;
            long long b = 0;
            for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) {
                    x = (pr[l].first * x + pr[l].second) % mod;
                    l++;
                }
                if (!(r & 1)) {
                    b = (a * pr[r].second + b) % mod;
                    a = (a * pr[r].first) % mod;
                    r--;
                }
            }
            cout << (a * x + b) % mod << '\n';
        }
    }
}
