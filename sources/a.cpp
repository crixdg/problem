#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;

int ti;
vector<int> disc, low;
vector<bool> vis;
vector<int> stk;
vector<vector<int>> sccs;

void dfs(int u) {
    disc[u] = low[u] = ti++;
    vis[u] = true;
    stk.push_back(u);

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (disc[u] == low[u]) {
        vector<int> scc;
        int v;
        do {
            v = stk.back();
            stk.pop_back();
            scc.push_back(v);
            vis[v] = false;
        } while (v != u);
        sccs.push_back(scc);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    ti = 0;
    disc.assign(n, -1);
    low.assign(n, -1);
    vis.resize(n);
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) { dfs(i); }
    }

    cout << sccs.size() << '\n';
    for (int i = sccs.size() - 1; i >= 0; i--) {
        cout << sccs[i].size() << ' ';
        for (int d : sccs[i]) { cout << d << ' '; }
        cout << '\n';
    }
}
