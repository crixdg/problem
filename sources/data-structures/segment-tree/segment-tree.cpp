#include <bits/stdc++.h>
using namespace std;

vector<long long> tr;

void update(int n, int i, int val) {
    for (i += n, tr[i] += val; i > 1; i >>= 1) {
        tr[i >> 1] = tr[i] + tr[i ^ 1];
    }
}

long long query(int n, int l, int r) {
    long long ans = 0;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) { ans += tr[l++]; }
        if (!(r & 1)) { ans += tr[r--]; }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    tr.resize(2 * n);
    for (int i = 0; i < n; i++) {
        int d;
        cin >> d;
        update(n, i, d);
    }
    while (q--) {

        int op;
        cin >> op;
        if (op == 0) {
            int p, x;
            cin >> p >> x;
            update(n, p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(n, l, r - 1) << '\n';
        }
    }
}
