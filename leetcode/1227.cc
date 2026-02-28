#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    double nthPersonGetsNthSeat(int n) {
        // sum (n-1) C (0..n-1) is the number of way persons get seat.
        // a.k.a number subset of n-1 elements = 2^(n-1);
        // sum (n-2) C (0..n-2) is the number of way persons get seat then n
        // can't get his own seat. a.k.a number subset of n-2 elements =
        // 2^(n-2);
        return 0.5;
    }
};
