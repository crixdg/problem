#include <bits/stdc++.h>
using namespace std;

void counting_sort(vector<int> &nums, int k) {
    int n = nums.size();
    vector<int> ans(n);
    int count[10] = {0};

    // count digit occurences
    for (int i = 0; i < n; i++) {
        int d = nums[i] / k % 10;
        count[d]++;
    }

    // prefix sum occurences
    for (int i = 1; i < 10; i++) { count[i] += count[i - 1]; }

    // build ans
    for (int i = n - 1; i >= 0; i--) {
        int d = nums[i] / k % 10;
        ans[count[d] - 1] = nums[i];
        count[d]--;
    }
    nums = ans;
}

void radix_sort(vector<int> &nums) {
    int max_val = *max_element(begin(nums), end(nums));
    for (int k = 1; max_val / k > 0; k *= 10) { counting_sort(nums, k); }
}

int main() {
    vector<int> nums = {170, 45, 75, 90, 802, 24, 2, 66};
    radix_sort(nums);
    for (int d : nums) { cout << d << ' '; }
    cout << '\n';
    return 0;
}
