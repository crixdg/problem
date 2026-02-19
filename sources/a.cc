#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> za(n);
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (i < j + za[j]) { za[i] = min(j + za[j] - i, za[i - j]); }
        while (i + za[i] < n && s[za[i]] == s[i + za[i]]) { za[i]++; }
        if (i + za[i] > j + za[j]) { j = i; }
    }
    za[0] = n;
    for (int i = 1; i < n; i++) {
        if (za[i] == n - i && za[i] % i == 0) {
            cout << "YES" << '\n';
            return 0;
        }
    }
    cout << "NO" << '\n';
    return 0;
}
