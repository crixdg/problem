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
    values.clear();
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

template <typename T> void __cout(const T &x);
template <typename T, typename V> void __cout(const pair<T, V> &x);
template <typename T, typename V, typename K>
void __cout(const tuple<T, V, K> &x);

void __cout(int x) { cout << x; }
void __cout(long x) { cout << x; }
void __cout(long long x) { cout << x; }
void __cout(unsigned x) { cout << x; }
void __cout(unsigned long x) { cout << x; }
void __cout(unsigned long long x) { cout << x; }
void __cout(float x) { cout << x; }
void __cout(double x) { cout << x; }
void __cout(long double x) { cout << x; }
void __cout(char x) { cout << '\'' << x << '\''; }
void __cout(const char *x) { cout << '\"' << x << '\"'; }
void __cout(const string &x) { cout << '\"' << x << '\"'; }
void __cout(bool x) { cout << (x ? "true" : "false"); }
void __cout(const vector<bool> &x) {
    int f = 0;
    cout << '{';
    for (auto i : x) { cout << (f++ ? ", " : ""), __cout(i); }
    cout << "}";
}

template <typename T> void __cout(const T &x) {
    int f = 0;
    cout << '{';
    for (auto &i : x) { cout << (f++ ? ", " : ""), __cout(i); }
    cout << "}";
}

template <typename T, typename V> void __cout(const pair<T, V> &x) {
    cout << '{', __info(x.first), cout << ", ", __cout(x.second), cout << '}';
}

template <typename T, typename K, typename V>
void __cout(const tuple<T, K, V> &x) {
    cout << '{', __info(get<0>(x)), cout << ", ", __info(get<1>(x)),
            cout << ", ", __info(get<2>(x)), cout << '}';
}

void __print() { cout << ']' << nl; }

template <typename T, typename... V> void __print(T t, V... v) {
    __cout(t);
    if (sizeof...(v)) { cout << ", "; }
    __print(v...);
}

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
        __cout(result);
        cout << nl;
    }
}

// * START ******************************************************************

class Solution {
    long long f[16][2][2][2][2][10][150];
    bool vs[16][2][2][2][2][10][150];

public:

    bool is_good(int n) {
        string s = to_string(n);
        if (s.size() <= 1) { return true; }
        bool inc = s[1] > s[0];
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1]) { return false; }
            if (inc != (s[i] > s[i - 1])) { return false; }
        }
        return true;
    }

    long long dfs(string &s, int pos, bool tight, bool leading_zero,
                  bool broken, bool increasing, int current, int sum_digits) {
        if (pos == s.size()) { return int(!broken || is_good(sum_digits)); }

        // dp state
        if (vs[pos][tight][leading_zero][broken][increasing][current]
              [sum_digits]) {
            return f[pos][tight][leading_zero][broken][increasing][current]
                    [sum_digits];
        }

        long long &ans = f[pos][tight][leading_zero][broken][increasing]
                          [current][sum_digits];
        vs[pos][tight][leading_zero][increasing][broken][current][sum_digits] =
                true;

        int limit = tight ? (s[pos] - '0') : 9;
        for (int i = 0; i <= limit; i++) {
            if (leading_zero) {
                if (i == 0) {
                    ans += dfs(s, pos + 1, tight && i == limit, true, false,
                               increasing, 0, 0);
                } else {
                    ans += dfs(s, pos + 1, tight && i == limit, false, false,
                               true, i, i);
                }
            } else if (broken) {
                ans += dfs(s, pos + 1, tight && i == limit, false, true, true,
                           i, sum_digits + i);
            } else if (sum_digits < 10) {
                if (i > current) {
                    ans += dfs(s, pos + 1, tight && i == limit, false, false,
                               true, i, sum_digits + i);
                } else if (i < current) {
                    ans += dfs(s, pos + 1, tight && i == limit, false, false,
                               false, i, sum_digits + i);
                } else {
                    ans += dfs(s, pos + 1, tight && i == limit, false, true,
                               true, i, sum_digits + i);
                }
            } else {
                if (increasing) {
                    if (i <= current) {
                        ans += dfs(s, pos + 1, tight && i == limit, false, true,
                                   true, i, sum_digits + i);
                    } else {
                        ans += dfs(s, pos + 1, tight && i == limit, false,
                                   false, true, i, sum_digits + i);
                    }
                } else {
                    if (i >= current) {
                        ans += dfs(s, pos + 1, tight && i == limit, false, true,
                                   true, i, sum_digits + i);
                    } else {
                        ans += dfs(s, pos + 1, tight && i == limit, false,
                                   false, false, i, sum_digits + i);
                    }
                }
            }
        }
        return ans;
    }

    long long countFancy(long long l, long long r) {
        memset(f, 0, sizeof(f));
        memset(vs, false, sizeof(vs));
        string ls = to_string(l - 1);
        long long lv = dfs(ls, 0, true, true, false, true, 0, 0);

        memset(f, 0, sizeof(f));
        memset(vs, false, sizeof(vs));
        string rs = to_string(r);
        long long rv = dfs(rs, 0, true, true, false, true, 0, 0);

        return rv - lv;
    }
};

// * END
// ********************************************************************

void solve(int test_case [[maybe_unused]]) {
    // UPDATE problemMethodName & inputs HERE
    long long l1;
    perform(Solution(), &Solution::countFancy, l, l1);
}

// **************************************************************************

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int test_cases = 1;
    __read(test_cases);
    while (test_cases--) { solve(test_cases); }
    cout << flush;
    return 0;
}

// **************************************************************************
// *author* Crix Dang
// **************************************************************************
