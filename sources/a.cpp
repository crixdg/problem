#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> par, sz;

int find(int x) {
    if (par[x] == x) { return x; }
    return par[x] = find(par[x]);
}

bool unite(int x, int y) {
    int u = find(x);
    int v = find(y);
    if (u != v) {
        if (sz[u] < sz[v]) { swap(u, v); }
        par[v] = u;
        sz[u]++;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    par.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++) { par[i] = i; }

    long long sm = 0;
    vector<int> ans;

    vector<vector<int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, i, u, v});
    }

    sort(begin(edges), end(edges));
    for (auto &i : edges) {
        if (unite(i[2], i[3])) {
            ans.push_back(i[1]);
            sm += i[0];
        }
    }

    cout << sm << '\n';
    for (int d : ans) { cout << d << ' '; }
    cout << '\n';
}
