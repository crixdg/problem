#include <bits/stdc++.h>
using namespace std;

void longestPalindromeSubstring(string &s) {
    int n = s.size();
    vector<int> f;

    int ansi = 0, ansl = 0;
    int c, r;

    // odd
    c = r = 0;
    f.assign(n, 0);
    for (int i = 0; i < n; i++) {
        // x ic x || c, r => c+1-r, c+r
        if (i < c + r) { f[i] = min(c + r - i, f[2 * c - i]); }
        while (i - f[i] >= 0 && i + f[i] < n && s[i - f[i]] == s[i + f[i]]) {
            f[i]++;
        }
        if (i + f[i] > c + r) { c = i, r = f[i]; }

        // additinal logics
        if (2 * f[i] - 1 > ansl) {
            ansl = 2 * f[i] - 1;
            ansi = i - f[i] + 1;
        }
    }

    // even
    c = r = 0;
    f.assign(n, 0);
    for (int i = 0; i < n; i++) {
        // x i x || c, r => c - r, c + r
        if (i < c + r) { f[i] = min(c + r - i, f[2 * c - i]); }
        while (i - f[i] - 1 >= 0 && i + f[i] < n &&
               s[i - f[i] - 1] == s[i + f[i]]) {
            f[i]++;
        }
        if (i + f[i] > c + r) { c = i, r = f[i]; }

        // additional logics
        if (2 * f[i] > ansl) {
            ansl = 2 * f[i];
            ansi = i - f[i];
        }
    }

    cout << s.substr(ansi, ansl) << '\n';
}

int main() {
    string s("abcbdkjcjkdbcd");
    longestPalindromeSubstring(s);
}
