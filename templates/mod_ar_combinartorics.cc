#include "modular.cc"
#include <bits/stdc++.h>

using namespace std;

/** ----------------------------- COMBINATORICS (ARBITRARY MODULUS) ----------------------------- **/

// TODO: Chinese Remainder Theorem
template <integer_c T, T *M_>
class combinatorics_arbitrary_t {
public:
  using _Mt = modular_t<T, M_>;
  combinatorics_arbitrary_t() {}
  combinatorics_arbitrary_t(int n) {}
};

using comb_ar_t = combinatorics_arbitrary_t<mod_t, &md>;
