#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<int> color;
deque<int> stk;
vector<int> pos;

bool dfs(int u) {
    color[u] = 1;
    pos[u] = stk.size();
    for (auto [v, e] : adj[u]) {
        stk.push_back(e);
        if (color[v] == 0) {
            if (dfs(v)) { return true; }
        } else if (color[v] == 1) {
            stk.erase(begin(stk), begin(stk) + pos[v]);
            cout << stk.size() << '\n';
            for (int d : stk) { cout << d << '\n'; }
            return true;
        }
        stk.pop_back();
    }
    color[u] = 2;
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
    }

    color.resize(n);
    pos.resize(n);
    for (int i = 0; i < n; i++) {
        if (color[i] == 0 && dfs(i)) { return 0; }
    }
    cout << -1 << '\n';
    return 0;
}
