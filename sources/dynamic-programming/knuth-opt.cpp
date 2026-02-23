#include <bits/stdc++.h>
using namespace std;

// dp[i][j] = min(dp[i][k] + dp[k][j] + cost(j, i)) with i < k < j
