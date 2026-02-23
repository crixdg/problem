#include <bits/stdc++.h>
using namespace std;

string s;
int f[10][2][10];
bool vs[10][2][10];

int dfs(int pos, bool tight, int count) {
    if (pos >= s.size()) { return count; }
    if (vs[pos][tight][count]) { return f[pos][tight][count]; }
    vs[pos][tight][count] = true;
    int &ans = f[pos][tight][count];
    ans = 0;

    int limit = tight ? s[pos] - 'a' : 9;
    for (int i = 0; i <= limit; i++) {
        ans += dfs(pos + 1, tight && i == limit, count + int(i == 1));
    }
    return ans;
}

int count_digit_one(int n) {
    s = to_string(n);
    memset(f, 0, sizeof(f));
    memset(vs, false, sizeof(vs));
    return dfs(0, true, 0);
}
