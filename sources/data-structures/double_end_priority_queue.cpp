#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int d;
        cin >> d;
        mp[d]++;
    }
    while (q--) {
        int op, x;
        cin >> op;
        if (op == 0) {
            cin >> x;
            mp[x]++;
        } else if (op == 1) {
            cout << mp.begin()->first << '\n';
            if (--mp.begin()->second == 0) { mp.erase(mp.begin()); }
        } else if (op == 2) {
            cout << prev(mp.end())->first << '\n';
            if (--prev(mp.end())->second == 0) { mp.erase(prev(mp.end())); }
        }
    }
}
