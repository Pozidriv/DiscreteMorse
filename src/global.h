#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
extern const string OUT_DEFAULT;
extern const string OUT_LOG;

// Useful data files
extern const string ID_FILE;
extern const string OUT_FILE;
extern const string COSET_REPS_FILE;
extern const string OLD_ADJ_LISTS_FILE;

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
extern ofstream g_log_ptr;
extern ifstream g_id_ptr;
extern Matrix g_Id;

extern const string delimiter;
