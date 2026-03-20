#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

void solve([[maybe_unused]] int test_case) {
    int n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;

    ll ans = 0;
    unordered_map<char, int> freq;
    for (int j = 0, i = 0; j < n; j++) {
        freq[s[j]]++;
        while (j - i > r) {
            freq[s[i]]--;
            i++;
        }
        if (j - i >= l) { ans += freq[s[j]]; }
    }
    cout << ans << nl;
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
