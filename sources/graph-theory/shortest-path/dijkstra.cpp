#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int src, dest;
    cin >> n >> m;
    cin >> src >> dest;

    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    using pli = pair<long long, int>;
    vector<long long> f(n, LLONG_MAX);
    f[src] = 0;
    vector<int> g(n, -1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.emplace(0LL, src);

    while (!pq.empty()) {
        auto [uw, u] = pq.top();
        pq.pop();
        if (f[u] < uw) { continue; }
        for (auto [v, w] : adj[u]) {
            if (f[u] + w < f[v]) {
                f[v] = f[u] + w;
                g[v] = u;
                pq.emplace(f[v], v);
            }
        }
    }

    if (f[dest] == LLONG_MAX) {
        cout << -1 << '\n';
    } else {
        vector<int> tmp;
        int t = dest;
        while (t != -1) {
            tmp.push_back(t);
            t = g[t];
        }
        reverse(begin(tmp), end(tmp));
        cout << f[dest] << ' ' << tmp.size() - 1 << '\n';
        for (int i = 0; i < tmp.size() - 1; i++) {
            cout << tmp[i] << ' ' << tmp[i + 1] << '\n';
        }
    }
}
