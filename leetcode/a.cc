#include <bits/stdc++.h>
using namespace std;


int main() {
    vector<int> nums; // input array
                      // w(i, j);
    auto w = [&](int i, int j) { return nums[j] - nums[i]; };

    int n = nums.size();
    vector<vector<int>> f(n, vector<int>(n));
    vector<vector<int>> opt(n, vector<int>(n));

    // base cases
    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
        f[i][i] = 0;
    }

    // loop backward on i because opt[i][j] depends on opt[i+1][j];
    for (int i = n - 2; i >= 0; i--) {
        // loop forward on j because opt[i][j] depends on opt[i][j-1];
        for (int j = i + 1; j < n; j++) {
            int mn = INT_MAX;
            int cost = w(i, j);
            // opt(i, j-1) <= opt(i, j) <= opt(i+1, j);
            for (int o = opt[i][j - 1]; o <= min(j - 1, opt[i + 1][j]); o++) {
                int t = f[i][o] + f[o][j] + cost;
                if (t < mn) {
                    opt[i][j] = o;
                    mn = t;
                }
            }
            f[i][j] = mn;
        }
    }

    cout << f[0][n-1] << endl;
    return 0;
}

