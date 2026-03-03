#include <bits/stdc++.h>

using namespace std;

constexpr char nl = '\n';

// --------------------------------------------------------------------------
// Data structures (only Leetcode)

template <typename T> struct LinkedListNode;
template <typename T> struct BinaryTreeNode;

template <typename T> struct LinkedListNode {
    T val;
    LinkedListNode *next;

    LinkedListNode() : val(T()), next(nullptr) {}
    LinkedListNode(T x) : val(x), next(nullptr) {}
    LinkedListNode(T x, LinkedListNode *next) : val(x), next(next) {}
};

template <typename T> struct BinaryTreeNode {
    T val;
    BinaryTreeNode *left;
    BinaryTreeNode *right;

    BinaryTreeNode() : val(T()), left(nullptr), right(nullptr) {}
    BinaryTreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
    BinaryTreeNode(T x, BinaryTreeNode *left, BinaryTreeNode *right)
        : val(x), left(left), right(right) {}
};

#define ListNode LinkedListNode<int>
#define TreeNode BinaryTreeNode<int>

// --------------------------------------------------------------------------
// Read methods (only Leetcode)

template <typename T> void __cin(stringstream &ss, T &value) { ss >> value; }

void __cin(stringstream &ss, char &value) {
    char c;
    ss >> c >> value >> c;
}

void __cin(stringstream &ss, string &value) {
    char c;
    ss >> c, getline(ss, value, '"');
}

template <typename T, typename V>
void __cin(stringstream &ss, pair<T, V> &values) {
    char c;
    ss >> c;
    __cin(ss, values.first);
    ss >> c;
    __cin<V>(ss, values.second);
    ss >> c;
}

template <typename T> void __cin(stringstream &ss, vector<T> &values) {
    char c;
    ss >> c;

    while (ss.peek() != ']') {
        T value;
        __cin(ss, value);
        values.push_back(value);
        ss >> c;
        if (c == ']') { break; }
    }
}

void __read() {}

template <typename T, typename... V> void __read(T &t, V &...v) {
    string str;
    getline(cin, str);
    stringstream ss(str);
    __cin(ss, t);
    __read(v...);
}

// --------------------------------------------------------------------------

template <typename T> void __info(const T &x);
template <typename T, typename V> void __info(const pair<T, V> &x);
template <typename T, typename V, typename K>
void __info(const tuple<T, V, K> &x);

void __info(int x) { cerr << x; }
void __info(long x) { cerr << x; }
void __info(long long x) { cerr << x; }
void __info(unsigned x) { cerr << x; }
void __info(unsigned long x) { cerr << x; }
void __info(unsigned long long x) { cerr << x; }
void __info(float x) { cerr << x; }
void __info(double x) { cerr << x; }
void __info(long double x) { cerr << x; }
void __info(char x) { cerr << '\'' << x << '\''; }
void __info(const char *x) { cerr << '\"' << x << '\"'; }
void __info(const string &x) { cerr << '\"' << x << '\"'; }
void __info(bool x) { cerr << (x ? "true" : "false"); }

void __info(const vector<bool> &x) {
    int f = 0;
    cerr << '{';
    for (auto i : x) { cerr << (f++ ? ", " : ""), __info(i); }
    cerr << "}";
}

template <typename T> void __info(const T &x) {
    int f = 0;
    cerr << '{';
    for (auto &i : x) { cerr << (f++ ? ", " : ""), __info(i); }
    cerr << "}";
}

template <typename T, typename V> void __info(const pair<T, V> &x) {
    cerr << '{', __info(x.first), cerr << ", ", __info(x.second), cerr << '}';
}

template <typename T, typename K, typename V>
void __info(const tuple<T, K, V> &x) {
    cerr << '{', __info(get<0>(x)), cerr << ", ", __info(get<1>(x)),
            cerr << ", ", __info(get<2>(x)), cerr << '}';
}

void __print() { cerr << ']' << nl; }

template <typename T, typename... V> void __print(T t, V... v) {
    __info(t);
    if (sizeof...(v)) { cerr << ", "; }
    __print(v...);
}

#ifdef INFO
#define enable_info() cerr << "Enabling debug logging..." << nl;
#define info(x...)                                                             \
    cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = [";  \
    __print(x);                                                                \
    cerr << "\e[39m";
#else
#define enable_info()
#define info(x...)
#endif

// --------------------------------------------------------------------------
// Runner (only Leetcode)

vector<int> arr [[maybe_unused]], nums [[maybe_unused]];
vector<string> strs [[maybe_unused]];
vector<vector<int>> grid [[maybe_unused]];
vector<vector<string>> str_grid [[maybe_unused]];

int v [[maybe_unused]];
long long l [[maybe_unused]];
double d [[maybe_unused]];
char c [[maybe_unused]], ch [[maybe_unused]];
string s [[maybe_unused]], str [[maybe_unused]];

template <typename Obj, typename MemFn, typename... Args>
void perform(Obj &&obj, MemFn memfn, Args &&...args) {
    __read(args...);

    if constexpr (std::is_void_v<decltype(std::invoke(
                          memfn, std::forward<Obj>(obj),
                          std::forward<Args>(args)...))>) {
        std::invoke(memfn, std::forward<Obj>(obj), std::forward<Args>(args)...);
    } else {
        auto result = std::invoke(memfn, std::forward<Obj>(obj),
                                  std::forward<Args>(args)...);
        __info(result);
        cerr << nl;
    }
}

// * START ******************************************************************

class Solution {
public:

    int mod = 1e9 + 7;
    int countPartitions(vector<int> &nums, int k) {
        int n = nums.size();
        vector<int> mntr(2 * n, INT_MAX), mxtr(2 * n, INT_MIN);
        for (int i = 0; i < n; i++) {
            int j = i;
            for (j += n, mntr[j] = nums[i], mxtr[j] = nums[i]; j > 1; j >>= 1) {
                mntr[j >> 1] = min(mntr[j], mntr[j ^ 1]);
                mxtr[j >> 1] = max(mxtr[j], mxtr[j ^ 1]);
            }
        }

        vector<long long> f(n + 1), p(n + 2);
        p[n + 1] = 0;
        f[n] = 1;
        p[n] = 1;

        for (int i = n - 1; i >= 0; i--) {
            int l = i, r = n - 1;
            while (l < r) {
                int m = l + (r - l + 1 >> 1);
                int mn = INT_MAX, mx = INT_MIN;
                for (int tl = i + n, tr = m + n; tl <= tr; tl >>= 1, tr >>= 1) {
                    if (tl & 1) {
                        mn = min(mn, mntr[tl]);
                        mx = max(mx, mxtr[tl]);
                        tl++;
                    }
                    if (!(tr & 1)) {
                        mn = min(mn, mntr[tr]);
                        mx = max(mx, mxtr[tr]);
                        tr--;
                    }
                }
                if (mx - mn <= k) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            f[i] = (p[i + 1] - p[r + 2]) % mod;
            f[i] = (f[i] + mod) % mod;
            p[i] = (p[i + 1] + f[i]) % mod;
        }
        return f[0];
    }
};

// * END
// ********************************************************************

void solve(int test_case [[maybe_unused]]) {
    perform(Solution(), &Solution::countPartitions, nums, v);
}

// **************************************************************************

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    enable_info();
    int test_cases = 1;
    // cin >> test_cases;
    while (test_cases--) {
        solve(test_cases);
        cout << flush;
    }
    return 0;
}

// **************************************************************************
// *author* Keiron Dang
// **************************************************************************
