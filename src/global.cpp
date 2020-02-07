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
// S: string
// F: file (stream)
// DATA: data file (string)
// I: int
// O: option
// OUT: outfile (string) [data/error/log]
//-----------------------------------------------------------------
// Default output file (generated data)
const string OUT_DEFAULT = "out/out.txt";
// Default log file (runtime log, sanity checks, errors, etc...)
const string OUT_LOG = "out/log.txt";

// Useful data files
//-----------------------------------------------------------------
// Identity matrix
const string ID_FILE = "data/4x4Id.txt";
// obsolete?
const string OUT_FILE = "out/quotient_elements.txt"; 
// coset representatives of subgroup H := { M | M = Id (mod 3) }
const string DATA_COSET_REPS = "data/coset_reps_mod3.txt"; 
// starting data (generators?) of G := O(Q) for Q = x^2 + y^2 + z^2 - 7t^2
const string DATA_START = "../data/starting_data.txt";
// Default elements to generate the quotient G/H as described above (generating coset representatives, O_crepes)
const string DATA_GENERATOR1 = "data/gen1.txt";
const string DATA_GENERATOR2 = "data/gen2.txt";
const string DATA_GENERATOR3 = "data/gen3.txt";
const string DATA_GENERATOR4 = "data/gen4.txt";
const string DATA_GENERATOR5 = "data/gen5.txt";
const string DATA_GENERATOR6 = "data/gen6.txt";
const string DATA_GENERATOR7 = "data/gen7.txt";
const string DATA_GENERATOR8 = "data/gen8.txt";
const string DATA_GENERATORS[8] = { 
   DATA_GENERATOR1, DATA_GENERATOR2, DATA_GENERATOR3, DATA_GENERATOR4,
   DATA_GENERATOR5, DATA_GENERATOR6, DATA_GENERATOR7, DATA_GENERATOR8
};

// Options, option argument format
//-----------------------------------------------------------------
// obsolete section?
const string O_DEF = "default";
const string O_TEST = "test";

// [] --> required argument
// {} --> optional argument
// X* --> multiple arguments
// O for option, OC for option (arguments) count
//-----------------------------------------------------------------
// obsolete counts?
const string O_KGEN = "k_blin_maker"; // Generating coset representatives using k generators
// run k_gen [number of generators]
const int OC_KGEC = 1;
const string O_CREPES = "crepes"; // Generating a minimal set of coset representatives
// run coset_reps [output file name] {generator1_file} {generator2_file}
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
//-----------------------------------------------------------------
// Log file
ofstream F_log;
// Input file
ifstream F_ifile;
// Output file
ofstream F_ofile;
// Identity matrix file
ifstream g_id_ptr;
// Identity matrix
Matrix g_Id;

// General purpose delimiter
const string delimiter = "------------------------";

// Constant parameters
//-----------------------------------------------------------------
// Expected number of coset representatives to compute (coset_representatives)
int I_EXPECTED_REP_NO = 720;
int I_MAX_GEN = 8;
