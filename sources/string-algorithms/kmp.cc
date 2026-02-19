#include <bits/stdc++.h>
using namespace std;

void patternMatching(string &s, string &p) {
    int m = p.size();
    vector<int> lsp(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && p[i] != p[j]) { j = lsp[j - 1]; }
        if (p[i] == p[j]) { j++; }
        lsp[i] = j;
    }

    int n = s.size();
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) { j = lsp[j - 1]; }
        if (s[i] == p[j]) { j++; }
        if (j == m) {
            cout << i - m + 1 << ' ';
            j = lsp[j - 1];
        }
    }
    cout << endl;
}

int main() {
    string s("abcbdbcbcbwab");
    string p("bcb");
    patternMatching(s, p);
    return 0;
}
