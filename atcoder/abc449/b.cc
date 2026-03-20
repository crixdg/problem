#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

void solve([[maybe_unused]] int test_case) {
    int h, w, q;
    cin >> h >> w >> q;
    while (q--) {
        int op, v;
        cin >> op >> v;
        if (op == 1) {
            cout << v * w << nl;
            h -= v;
        } else if (op == 2) {
            cout << v * h << nl;
            w -= v;
        }
    }
    // crixdg
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // cout << fixed << setprecision(10);
    // cout << fixed << setprecision(15);

    int t;
    // cin >> t;
    t = 1;
    while (t--) { solve(t); }
    return 0;
}
