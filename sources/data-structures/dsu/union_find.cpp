#include <bits/stdc++.h>
using namespace std;

vector<int> par, sz;

int parent(int x) {
    if (par[x] == x) { return x; }
    return par[x] = parent(par[x]);
}

void unite(int x, int y) {
    int u = parent(x);
    int v = parent(y);
    if (u != v) {
        if (sz[u] < sz[v]) { swap(u, v); }
        par[v] = u;
        sz[u]++;
    }
}

bool isConnected(int x, int y) {
    int u = parent(x);
    int v = parent(y);
    return u == v;
}

int main() {
    int n, q;
    cin >> n >> q;
    par.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++) { par[i] = i; }

    while (q--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 0) {
            unite(u, v);
        } else {
            cout << isConnected(u, v) << '\n';
        }
    }
}
