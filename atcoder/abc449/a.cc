#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

void solve([[maybe_unused]] int test_case) {
    int n;
    cin >> n;
    double r = (double)n / 2;
    cout << r * r * M_PI << nl;
    // crixdg
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cout << fixed << setprecision(10);
    // cout << fixed << setprecision(15);

    int t;
    // cin >> t;
    t = 1;
    while (t--) { solve(t); }
    return 0;
}
