#include <bits/stdc++.h>
using namespace std;

// dp[k][j] = min(dp[k-1][j] + cost(j, i)) with j<i;
// k is number of layers, example split an array into k group
// -- such that sum of f(each_group) is maximum.
