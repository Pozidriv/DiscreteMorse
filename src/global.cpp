#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _GLOBAL
#define _GLOBAL
#include "global.h"
#endif
using namespace std;

// Globals
const string OUT_DEFAULT = "out/out.txt";
const string OUT_LOG = "out/log.txt";

// Useful data files
const string ID_FILE = "data/4x4Id.txt";
const string OUT_FILE = "out/quotient_elements.txt";
const string COSET_REPS_FILE = "data/coset_reps_mod3.txt";
const string OLD_ADJ_LISTS_FILE = "../data/HypMan.txt";

// Options, option argument format
const string O_DEF = "default";
const string O_TEST = "test";

// [] --> required argument
// {} --> optional argument
// X* --> multiple arguments
// O for option, OC for option (arguments) count
const string O_KGEN = "k_blin_maker"; // Generating coset representatives using k generators
// run k_gen [number of generators]
const int OC_KGEC = 1;
const string O_CREPES = "crepes"; // Generating a minimal set of coset representatives
// run coset_reps [output file name] [expected number]
const int OC_CREPEC = 2;
const string O_ADJ_LISTS = "adj_liszt"; // Computing new adjacency lists
// run coset_reps [output file name]
const int OC_ADJ_LISTC = 1;
const string O_GRAPH_HOMOL = "guacomology"; // Computing the homology of a graph
const int OC_GRAPH_HOMOLC = 1;
const string O_MAGMA_CONV = "magma_convexion"; // Converting shitty magma matrix format into readable things
// run magma_conv [input file name] {output file name}
const int OC_MAGMA_CONC = 1;

// File pointers
ofstream g_log_ptr;
ifstream g_id_ptr;
Matrix g_Id;

const string delimiter = "------------------------";
