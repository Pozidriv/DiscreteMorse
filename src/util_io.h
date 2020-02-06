#ifndef _BITS
#include <bits/stdc++.h>
#define _BITS
#endif

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
