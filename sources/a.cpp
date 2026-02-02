#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    set<int> st;
    string T;
    cin >> T;
    for (int i = 0; i < T.size(); i++) {
        if (T[i] == '1') { st.insert(i); }
    }
    while (q--) {
        int op;
        cin >> op;
        int k;
        cin >> k;
        switch (op) {
        case 0:
            st.insert(k);
            break;
        case 1: {
            auto it = st.find(k);
            if (it != st.end()) { st.erase(it); }
            break;
        }
        case 2: {
            auto it = st.find(k);
            if (it != st.end()) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
            break;
        }
        case 3: {
            auto it = st.upper_bound(k - 1);
            if (it == st.end()) {
                cout << -1 << '\n';
            } else {
                cout << *it << '\n';
            }
            break;
        }
        case 4: {
            auto it = st.lower_bound(k);
            if (it == st.end()) {
                cout << -1 << '\n';
            } else if (*it == k) {
                cout << k << '\n';
            } else if (it == st.begin()) {
                cout << -1 << '\n';
            } else {
                cout << *(--it) << '\n';
            }
        }
        }
    }
}
