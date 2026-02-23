#include <bits/stdc++.h>
using namespace std;

string s;
int f[10][2][2][2][1 << 10];
bool vis[10][2][2][2][1 << 10];

int dfs(int pos, bool tight, bool leading_zero, bool repeated, int freq) {
    if (pos == s.size()) { return int(repeated); }
    if (vis[pos][tight][leading_zero][repeated][freq]) {
        return f[pos][tight][leading_zero][repeated][freq];
    }

    vis[pos][tight][leading_zero][repeated][freq] = true;
    int &ans = f[pos][tight][leading_zero][repeated][freq];
    ans = 0;

    int limit = tight ? s[pos] - '0' : 9;
    for (int i = 0; i <= limit; i++) {
        if (leading_zero) {
            if (i == 0) {
                ans += dfs(pos + 1, tight && i == limit, true, false, 0);
            } else {
                ans += dfs(pos + 1, tight && i == limit, false, false, 1 << i);
            }
        } else {
            ans += dfs(pos + 1, tight && i == limit, false,
                       repeated || (freq & (1 << i)), freq | (1 << i));
        }
    }
    return ans;
}

int num_dup_digit_as_most_n(int n) {
    s = to_string(n);
    memset(vis, false, sizeof(vis));
    return dfs(0, true, true, false, 0);
}

int main() {
    int n;
    cin >> n;
    cout << num_dup_digit_as_most_n(n) << '\n';
    return 0;
}
