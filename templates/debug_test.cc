#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) ((void)0)
#endif

int main() {
  short sh = SHRT_MAX;
  debug(sh);
  unsigned short ush = USHRT_MAX;
  debug(ush);

  int i = INT_MAX;
  debug(i);
  long l = LONG_MAX;
  debug(l);
  long long ll = LLONG_MAX;
  debug(ll);
  __int128_t i128 = LLONG_MAX;
  debug(i128);

  unsigned int ui = UINT_MAX;
  debug(ui);
  unsigned long ul = ULONG_MAX;
  debug(ul);
  unsigned long long ull = ULLONG_MAX;
  debug(ull);

  float f = FLT_MAX;
  debug(f);
  double d = DBL_MAX;
  debug(d);
  long double ld = LDBL_MAX;
  debug(ld);

  char c = 'a';
  debug(c);
  const char *cs = "hello";
  debug(cs);
  string s = "hello world";
  debug(s);

  bool b = true;
  debug(b);

  pair<int, int> p = {1, 2};
  debug(p);
  tuple<int, int, int> tpl = {1, 2, 3};
  debug(tpl);

  vector<int> v = {1, 2, 3};
  debug(v);
  array<int, 3> a = {1, 2, 3};
  debug(a);

  deque<int> dq = {1, 2, 3};
  debug(dq);
  list<int> lt = {1, 2, 3};
  debug(lt);

  stack<int> stk;
  stk.push(1);
  stk.push(2);
  stk.push(3);
  debug(stk);

  queue<int> qu;
  qu.push(1);
  qu.push(2);
  qu.push(3);
  debug(qu);

  unordered_set<int> us = {1, 2, 3};
  set<int> st = {1, 2, 3};
  multiset<int> ms = {1, 2, 3};
  debug(us, st, ms);

  map<int, int> m = {{1, 2}, {3, 4}};
  unordered_map<int, int> um = {{1, 2}, {3, 4}};
  multimap<int, int> mm = {{1, 2}, {3, 4}};
  debug(m, um, mm);

  priority_queue<int> max_heap;
  max_heap.push(1);
  max_heap.push(2);
  max_heap.push(3);
  debug(max_heap);

  priority_queue<int, vector<int>, greater<int>> min_heap;
  min_heap.push(1);
  min_heap.push(2);
  min_heap.push(3);
  debug(min_heap);

  return 0;
}
