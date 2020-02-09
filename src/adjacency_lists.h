#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
#ifndef _UTIL_IO
#define _UTIL_IO
#include "util_io.h"
#endif
#ifndef _GLOBAL
#define _GLOBAL
#include "global.h"
#endif

// Compute adjacency lists based on stuff.
// Stuff:
// - cr_ptr, the file with the coset representatives g_i
// - oal_ptr, the file with the old adjacency lists L_{p,q}
void compute_adjacency_lists(ifstream& cr_ptr, ifstream& oal_ptr);

// Same, but in parallel
void par_CAL(ifstream& cr_ptr, ifstream& oal_ptr);
