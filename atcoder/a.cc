#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

void solve() {
    int d;
    cin >> d;
    double r = (double)d / 2;
    cout << r * r * M_PI << nl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cout << fixed << setprecision(15);
    solve();
    return 0;
}
