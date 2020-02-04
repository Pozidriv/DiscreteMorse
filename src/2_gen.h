// (22/10/2019) 
// Attempts to generate all elements of the group mod 3 using two specified elements
#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
#ifndef _GLOBAL
#define _GLOBAL
#include "global.h"
#endif

// Generate all elts mod3 generated by A,B and returns them in quotient_elements
// Checks if expected size is met
// Expects wordA, wordB to be a capitalized character
void two_gen(Matrix A, Matrix B, string wordA, string wordB,
             vector<Matrix> &quotient_elements, vector<string> &words, int expected_size);
