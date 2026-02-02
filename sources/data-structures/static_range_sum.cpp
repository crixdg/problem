#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> ps(n + 1);
    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        ps[i] = ps[i - 1] + d;
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << ps[r] - ps[l] << '\n';
    }
}
