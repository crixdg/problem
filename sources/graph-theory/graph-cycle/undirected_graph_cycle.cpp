#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<bool> vis;
vector<int> pos;
deque<pair<int, int>> stk;

bool dfs(int u, int ue) {
    vis[u] = true;
    pos[u] = stk.size();
    for (auto [v, e] : adj[u]) {
        if (ue == e) { continue; }
        stk.push_back({u, e});
        if (!vis[v]) {
            if (dfs(v, e)) { return true; }
        } else {
            stk.erase(begin(stk), begin(stk) + pos[v]);
            cout << stk.size() << '\n';
            for (auto [d, _] : stk) { cout << d << ' '; }
            cout << '\n';
            for (auto [_, d] : stk) { cout << d << ' '; }
            cout << '\n';
            return true;
        }
        stk.pop_back();
    }
    pos[u] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vis.resize(n);
    pos.resize(n);
    for (int i = 0; i < n; i++) {
        if (!vis[i] && dfs(i, -1)) { return 0; }
    }
    cout << -1 << '\n';
    return 0;
}
