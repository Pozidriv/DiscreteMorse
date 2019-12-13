#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
#ifndef _PARSING
#define _PARSING
#include "parsing.h"
#endif

// Would an enum be better?
#define MATRIX "matrix"
#define EDGE_LABEL "elabel"
#define EDGE_WITNESS "ewit"
#define MYFILE "file"


using namespace std;

// Parses for a specific object
string parse(ifstream in_file, string type) {
   string ret;
   if(type == MATRIX) {

   } else if(type == EDGE_LABEL) {

   } else if(type == EDGE_WITNESS) {

   } else if(type == MYFILE) {

   }

   return ret;
}

// Expected input file format:
// EDGE_LABEL: [n1,n2]
// EDGE_WITNESSES: [ { MATRIX, } MATRIX ]
// MATRIX: [ 16 comma separated integers ]
//
// FILE :
// { EDGE _LABEL }
void magma_parser(ifstream in_file, string out_filename) {


}
