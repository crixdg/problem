#include <bits/stdc++.h>
using namespace std;

void next_permutation(vector<int> &nums) {
    int n = nums.size();
    int u, v;

    // find pivot (first decreased value from the right)
    for (u = n - 2; u >= 0; u--) {
        if (nums[u] < nums[u + 1]) { break; }
    }

    // check if array isn't decending at all
    if (u >= 0) {
        // first successor which value is greater than pivot value from the right
        for (v = n - 1; v > u; v--) {
            if (nums[v] > nums[u]) { break; }
        }
        
        // swap pivot and successor
        swap(nums[u], nums[v]);
    }
    
    // reverse the suffix
    reverse(begin(nums) + u + 1, end(nums));
}

int main() {
    vector<int> nums{5, 4, 4, 3};
    next_permutation(nums);
    for (int d : nums) { cout << d << ' '; }
    cout << '\n';
    return 0;
}
