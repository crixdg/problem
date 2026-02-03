#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> nums(n);
vector<int> differenceArray(n + 1);

void update(int l, int r, int val) {
    differenceArray[l] += val;
    differenceArray[r + 1] -= val;
}

void rebuild() {
    for (int i = 0; i < n; i++) {
        if (i > 0) { differenceArray[i] += differenceArray[i - 1]; }
        nums[i] += differenceArray[i];
    }
    differenceArray.assign(n + 1, 0);
}

int main() {
    nums = {1, 2, 3, 4, 5, 6};
    n = nums.size();
    differenceArray.assign(n + 1, 0);

    update(1, 2, 3);
    update(2, 4, 1);
    rebuild();
    for (int i = 0; i < n; i++) { cout << nums[i] << ' '; }
    cout << endl;
}
