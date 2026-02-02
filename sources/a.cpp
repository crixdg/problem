#include <bits/stdc++.h>
using namespace std;

vector<int> tr;

void update(int n, int i, bool isInsert) {
    for (i += n, tr[i] = isInsert; i > 1; i >>= 1) {
        tr[i >> 1] = tr[i] + tr[i ^ 1];
    }
}

int queryMaxSmaller(int n, int l, int r) {}

int main() {
    int n, q;
    cin >> n >> q;
    string T;
    cin >> T;

    tr.assign(2 * n, 0);
    for (int i = 0; i < T.size(); i++) {
        if (T[i] == '1') { update(n, i, 1); }
    }
    while (q--) {
        int op, k;
        cin >> op >> k;
        switch (op) {
        case 0:
            update(n, k, 1);
            break;
        case 1: {
            update(n, k, 0);
            break;
        }
        case 2: {
            if (tr[k + n]) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
            break;
        }
        case 3: {
            int l = k, r = n - 1;
            int ans = INT_MIN;
            for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) {}
            }
            break;
        }
        case 4: {
            int l = 0, r = k;
        }
        }
    }
}
