#include <bits/stdc++.h>
#include <cmath>
using namespace std;

vector<int> tr;

void update(int n, int i, bool isInsert) {
    for (i += n, tr[i] = isInsert; i > 1; i >>= 1) {
        tr[i >> 1] = tr[i] + tr[i ^ 1];
    }
}

int queryMaxSmaller(int n, int l, int r) {
    int ans = INT_MIN;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
        if (!(r & 1)) {
            if (tr[r] > 0) {
                int v = r;
                while (v < n) {
                    if (tr[v * 2 + 1] > 0) {
                        v = v * 2 + 1;
                    } else {
                        v = v * 2;
                    }
                }
                return v - n;
            }
            r--;
        }
        if (l & 1) {
            if (tr[l] > 0) {
                int v = l;
                while (l < n) {
                    if (tr[v * 2 + 1] > 0) {
                        v = v * 2 + 1;
                    } else {
                        v = v * 2;
                    }
                }
                ans = max(ans, v - n);
            }
            l++;
        }
    }
    if (ans == INT_MIN) { return -1; }
    return ans;
}

int queryMinGreater(int n, int l, int r) {
    int ans = INT_MAX;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (tr[l] > 0) {
                int v = l;
                while (l < n) {
                    if (tr[v * 2 + 1] > 0) {
                        v = v * 2 + 1;
                    } else {
                        v = v * 2;
                    }
                }
                return v - n;
            }
            l++;
        }
        if (!(r & 1)) {
            if (tr[r] > 0) {
                int v = r;
                while (v < n) {
                    if (tr[v * 2 + 1] > 0) {
                        v = v * 2 + 1;
                    } else {
                        v = v * 2;
                    }
                }
                ans = min(ans, v - n);
            }
            r--;
        }
    }
    if (ans == INT_MAX) { return -1; }
    return ans;
}

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
            cout << queryMinGreater(n, k, n - 1) << '\n';
            break;
        }
        case 4: {
            cout << queryMaxSmaller(n, 0, k) << '\n';
        }
        }
    }
}
