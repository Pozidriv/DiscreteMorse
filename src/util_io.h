#ifndef BITS
#include <bits/stdc++.h>
#define BITS
#endif

// Add verboses as you want functions to shut up
// Don't forget to modify the .inl file accordingly
// Make sure you keep the precedence when you add new verboses
#define VERBOSE 1
#define MATRIX_VERBOSE 1

using namespace std;


void narrator(void);
string paction(void);

template<typename First, typename ... Strings>
void narrator(First arg, const Strings&... rest);

template<typename First, typename ... Strings>
void debug(First fnct, const Strings&... rest);

#ifndef UTILIO_INL
#define UTILIO_INL
#include "util_io.inl"
#endif
