#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    unordered_map<long long, long long> mp;
    while (q--) {
        int op;
        long long k, v;

        cin >> op;
        if (op == 0) {
            cin >> k >> v;
            mp[k] = v;
        } else if (op == 1) {
            cin >> k;
            cout << mp[k] << '\n';
        }
    }
    cout << flush;
}
