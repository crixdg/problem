#include "../templates/dsu.cc"
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  {
    dsu_t dsu(n);
    while (q--) {
      int op, u, v;
      cin >> op >> u >> v;
      {
        if (op == 0) {
          dsu.unite(u, v);
        } else if (op == 1) {
          cout << int(dsu.same(u, v)) << '\n';
        }
      }
    }
  }
  return 0;
}
