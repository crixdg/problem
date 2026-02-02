#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> as(n);
    for (int &d : as) { cin >> d; }
    while (q--) {
        int op, x;
        cin >> op >> x;
        switch (op) {
            case 0: {
                // insert x into S
                break;
            }
            case 1: {
                // erase x from S
                break;
            }
            case 2: {
                // output the x-th smallest number of S in asc, or -1
                break;
            }
            case 3: {
                // output the number of element in S that are less than or equal to x
            }
            case 4: {
                // output the largest element that lower than or equal to x, or -1
                break;
            }
            case 5: {
                // output the smallest element that greater than or equal to x, or -1
                break;
            }
        }
    }
}
