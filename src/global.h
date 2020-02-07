#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
extern const string OUT_DEFAULT;
extern const string OUT_LOG;

// Useful data files
extern const string ID_FILE;
extern const string OUT_FILE;
extern const string DATA_COSET_REPS;
extern const string DATA_START;
extern const string DATA_GENERATOR1;
extern const string DATA_GENERATOR2;
extern const string DATA_GENERATOR3;
extern const string DATA_GENERATOR4;
extern const string DATA_GENERATOR5;
extern const string DATA_GENERATOR6;
extern const string DATA_GENERATOR7;
extern const string DATA_GENERATOR8;
extern const string DATA_GENERATORS[8];

// Options, option argument format
extern const string O_DEF;
extern const string O_TEST;

// [] --> required argument
// {} --> optional argument
// X* --> multiple arguments
// O for option, OC for option (arguments) count
extern const string O_KGEN; // Generating coset representatives using k generators
// run k_gen [number of generators]
extern const int OC_KGEC;
extern const string O_CREPES; // Generating a minimal set of coset representatives
// run coset_reps [output file name] [expected number]
extern const int OC_CREPEC;
extern const string O_ADJ_LISTS; // Computing new adjacency lists
// run coset_reps [output file name]
extern const int OC_ADJ_LISTC;
extern const string O_GRAPH_HOMOL; // Computing the homology of a graph
extern const int OC_GRAPH_HOMOLC;
extern const string O_MAGMA_CONV; // Converting shitty magma matrix format into readable things
// run magma_conv [input file name] {output file name}
extern const int OC_MAGMA_CONC;

// File pointers
extern ofstream F_log;
extern ifstream F_ifile;
extern ofstream F_ofile;
extern ifstream g_id_ptr;
extern Matrix g_Id;

extern const string delimiter;

// Constant parameters
extern int I_EXPECTED_REP_NO; // Expected nubmer of coset representatives (crepes)
extern int I_MAX_GEN;         // Max number of generators to be used (crepes)
