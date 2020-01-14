#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
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

#define OUT_DEFAULT "out/out.txt"

// Useful data files
#define ID_FILE "data/4x4Id.txt"
#define OUT_FILE "out/quotient_elements.txt"
#define COSET_REPS_FILE "data/coset_reps_mod3.txt"
#define OLD_ADJ_LISTS_FILE "../data/HypMan.txt"

// Options, option argument format
#define O_DEF "default"
#define O_TEST "test"

// [] --> required argument
// {} --> optional argument
// X* --> multiple arguments
// O for option, OC for option (arguments) count
#define O_KGEN "k_blin_maker" // Generating coset representatives using k generators
// run k_gen [number of generators]
#define OC_KGEC 1
#define O_CREPES "crepes" // Generating a minimal set of coset representatives
// run coset_reps [output file name] [expected number]
#define OC_CREPEC 2
#define O_ADJ_LISTS "adj_liszt" // Computing new adjacency lists
// run coset_reps [output file name]
#define OC_ADJ_LISTC 1
#define O_GRAPH_HOMOL "guacomology" // Computing the homology of a graph
#define OC_GRAPH_HOMOLC 1
#define O_MAGMA_CONV "magma_convexion" // Converting shitty magma matrix format into readable things
// run magma_conv [input file name] {output file name}
#define OC_MAGMA_CONC 2


using namespace std;

void O_kgen(string, vector<string>);
void O_crepes(string, vector<string>);
void O_adj_lists(string, vector<string>);
void O_graph_homol(string, vector<string>);
void O_magma_conv(string, vector<string>);

// Globals (put in a separate file?)
ofstream g_log_ptr;
ifstream g_id_ptr;
Matrix g_Id;

const string delimiter = "------------------------";


int main(int argc, char *argv[]) {
   if(argc < 2) {
      narrator("Usage:");
      narrator("run [-mode] {arguments}");
      return 0;
   }
   cout << "========= Running Main =========" << endl;

   vector<string> modes = { O_KGEN, O_CREPES, O_ADJ_LISTS, O_GRAPH_HOMOL, O_MAGMA_CONV };

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
            cout << modes[i] << (i==modes.size()-1)?"]":"|";
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
   g_log_ptr.open("Out/log.txt", ofstream::out);
   g_id_ptr.open(ID_FILE, ifstream::in);
   g_Id = Matrix(g_id_ptr, 4);


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
void O_crepes(string filename, vector<string> args) {
   narrator("Not yet implemented");
}
void O_adj_lists(string filename, vector<string> args) {
   narrator("Not yet implemented");
}
void O_graph_homol(string filename, vector<string> args) {
   narrator("Not yet implemented");
}
void O_magma_conv(string filename, vector<string> args) {
   narrator("Magma Parser");
   narrator(delimiter);
   
   if(args.size()==0) {
      narrator("No outfile specified. Using default:", OUT_DEFAULT);
   }

   ofstream ofile;
   ofile.open(ofstream::in, OUT_DEFAULT);

   
}
