#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _GLOBAL
#define _GLOBAL
#include "global.h"
#endif
#ifndef _UTIL_IO
#define _UTIL_IO
#include "util_io.h"
#endif
#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
#ifndef _MAGMA_PARSER
#define _MAGMA_PARSER
#include "magma_parser.h"
#endif
#ifndef _2_GEN
#define _2_GEN
#include "2_gen.h"
#endif
#ifndef _ADJACENCY_LISTS
#define _ADJACENCY_LISTS
#include "adjacency_lists.h"
#endif



using namespace std;

void O_kgen(string, vector<string>);
void O_crepes(string, vector<string>);
void O_adj_lists(string, vector<string>);
void O_graph_homol(string, vector<string>);
void O_magma_conv(string, vector<string>);




int main(int argc, char *argv[]) {
   if(argc < 2) {
      narrator("Usage:");
      narrator("run [-mode] {arguments}");
      return 0;
   }
   cout << "========= Running Main =========" << endl;

   vector<string> modes = { "default", O_KGEN, O_CREPES, O_ADJ_LISTS, O_GRAPH_HOMOL, O_MAGMA_CONV };

   string token, file, out;
   vector<string> arguments;
   int fstart=1, mode=0;
   
   // Mode
   if(argv[1][0] == '-') {
      fstart++;
      token = argv[1];
      if(token.size() == 1) {
         narrator("Unrecognized option \"\"");
         cout << "Available options: [";
         for(int i=0;i<modes.size();i++) {
            cout << modes[i];
            if (i==modes.size()-1) {
               cout << "]";
            } else {
               cout << "|";
            }
         }
         cout << endl;
         return 0;
      }
      token = token.substr(1);
      
      int flag=0;
      for(int i=0; i<modes.size(); i++) {
         if(modes[i] == token) {
            flag = 1;
            mode = i;
            break;
         }
      }
      if(!flag) {
         narrator("Unrecognized option \"", token, "\"");
         cout << "Available options: [";
         for(int i=0;i<modes.size();i++) {
            cout << modes[i];
            if(i==modes.size()-1) {
               cout << "]";
            } else {
               cout << "|";
            }
         }
         cout << endl;
         return 0;
      }

      // Recover the rest of the arguments
      for(int i=2; i<argc; i++) {
         token = argv[i];
         arguments.push_back(token);
      }
   }
   F_log.open(OUT_LOG, ofstream::out);
   log("Globals\n", delimiter);
   log("Default out file:", OUT_FILE);
   log("Identity file:", ID_FILE);
   log("Coset representatives file:", DATA_COSET_REPS);
   log("Starting adjacency lists file:", DATA_START);
   log(delimiter);

   g_id_ptr.open(ID_FILE, ifstream::in);
   g_Id.rows = 4;
   g_Id.cols = 4;
   g_Id.entries = vector<vector<long int> >(4, vector<long int>(4));
   g_Id = Matrix(g_id_ptr, 4);

   log("Mode:", modes[mode]);


   // Ex
   switch(mode) {
      case 0 : // M_DEF
               narrator("No default implemented");
               break;
      case 1 : // 
               narrator("Option: k_gen");
               O_kgen(file, arguments);
               break;
      case 2 : // 
               narrator("Option: coset_reps");
               O_crepes(file, arguments);
               break;
      case 3 : // 
               narrator("Option: adj_lists");
               O_adj_lists(file, arguments);
               break;
      case 4 : // 
               narrator("Option: graph_homology");
               O_graph_homol(file, arguments);
               break;
      case 5 : // 
               narrator("Option: magma_conv");
               O_magma_conv(file, arguments);
               break;
      default: 
               narrator("No default implemented");
               break;
   }

   return 0;
}

void O_kgen(string filename, vector<string> args) {
   narrator("Not yet implemented");
}

// { filename } { gen1_file } { gen_2_file }
void O_crepes(string filename, vector<string> args) {
   narrator("Generating Coset Representatives for a Subgroup");
   narrator(delimiter);
   narrator("Expecting", I_EXPECTED_REP_NO, "elements.");

   string ofile_name = OUT_DEFAULT;
   if(args.size()==0) {
      narrator("No output file specified. Using default:", OUT_DEFAULT);
   } else {
      filename = args[0];
   }
   if(args.size() < 2) {
      narrator("Using default generators");
   }
   F_ofile.open(ofile_name, ofstream::out);
   F_ifile.open(filename, ifstream::in);

   // Setup
   vector<Matrix> coset_representatives;

   two_gen(coset_representatives, I_EXPECTED_REP_NO);
   
   // Print results (keep track of matrices?)
   narrator("Printing coset representatives to file.");
   F_ofile << coset_representatives.size() << endl;
   for(int i=0; i<coset_representatives.size(); i++) {
      F_ofile << endl;
      coset_representatives[i].print(F_ofile);
   }
}

// Input file: old adjacency lists L_{p,q}
// Output file: new adjacency lists L_{g_i p, g_j q}
void O_adj_lists(string filename, vector<string> args) {
   string ofile_name = OUT_DEFAULT;

   narrator("Computing Adjacency Lists for a Subgroup");
   narrator(delimiter);
   if(args.size()==0) {
      narrator("No out file specified. Using default:", OUT_DEFAULT);
   } else {
      ofile_name = args[0];
   }
   F_ofile.open(ofile_name, ofstream::out);

   // Setup coset representatives and old adjacency lists files
   ifstream cr_ptr, oal_ptr;
   cr_ptr.open(DATA_COSET_REPS);
   oal_ptr.open(DATA_START);
   //compute_adjacency_lists(cr_ptr, oal_ptr); // OPTIMIZATION: compute this in parallel
   par_CAL(cr_ptr, oal_ptr);

   F_ofile.close();
}
void O_graph_homol(string filename, vector<string> args) {
   narrator("Not yet implemented");
}

// filename { output_file }
void O_magma_conv(string filename, vector<string> args) {
   string ofile_name = OUT_DEFAULT;

   narrator("Magma Parser");
   narrator(delimiter);
   if(args.size()==0) {
      narrator("No file to convert specified");
      exit(1);
   } else {
      filename = args[0];
      if(args.size() < 2) {
         narrator("No out file specified. Using default:", OUT_DEFAULT);
      } else {
      }
   }
   log("Input file:", filename);
   F_ofile.open(ofile_name, ofstream::out);
   F_ifile.open(filename, ifstream::in);

   vector<vector<Matrix>> matrices;
   vector<vector<int>> elabels;

   debug("O_magma_conv", "Reading file");
   magma_4x4read(F_ifile, matrices, elabels);
   log("Finished reading file.");
   log("Matrices:", matrices.size(), "| Elabels:", elabels.size());
   cout << elabels.size() << endl;
   readable_write(F_ofile, matrices, elabels);
   log("Finished writing to file.");
   F_ofile.close();
   F_ifile.close();
}
