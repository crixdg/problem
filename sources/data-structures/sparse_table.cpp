#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> lg(n + 1);
    for (int i = 2; i <= n; i++) { lg[i] = lg[i / 2] + 1; }

    vector<vector<int>> st(20, vector<int>(n));
    for (int i = 0; i < n; i++) { cin >> st[0][i]; }
    for (int k = 1; k < 20; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        int k = lg[r - l];
        cout << min(st[k][l], st[k][r - (1 << k)]) << '\n';
    }
}
