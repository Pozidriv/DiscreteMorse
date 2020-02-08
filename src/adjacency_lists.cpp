#ifndef _ADJACENCY_LISTS
#define _ADJACENCY_LISTS
#include "adjacency_lists.h"
#endif

// Formula for new adajacency lists
// L_{g_{i}p, g_{j}q} = g_{j}^{-1} L_{p,q} g_{i} \cap H, where H is the subgroup
// Globals:
// - F_ofile, the file to print the garbage to
// - F_ifile, useless
// - F_log, the log file
// OPTIMIZATION: parallel compute
void compute_adjacency_lists(ifstream& cr_ptr, ifstream& oal_ptr) {
   // Retrieve old adjacency lists
   vector<vector<Matrix>> oal;   // Witnesses of adjacency: one list for each adjacency 
   vector<vector<int>> elabels;  // Edge labels: vector of pairs (a, b)
   int adj_no;                   // Number of adjacency lists

   oal_ptr >> adj_no;
   debug("compute_adjacency_lists", "Reading", adj_no, "lists");

   for(int i=0; i<adj_no; i++) {
      int a,b,witness_no;        // witness_no: number of witnesses
      vector<Matrix> witness_list;
      oal_ptr >> a >> b >> witness_no;
      elabels.push_back({a, b});
      debug("compute_adjacency_lists", "Edge label:", a, b);
      
      for(int j=0; j<witness_no; j++) {
         witness_list.push_back(Matrix(oal_ptr, 4));
      }
      oal.push_back(witness_list);
   }

   // Retrieve coset representatives
   vector<Matrix> coset_reps;    // Coset representatives
   int cr_no;                    // Number of coset representatives

   cr_ptr >> cr_no;
   debug("compute_adjacency_lists", "Reading", cr_no, "coset representatives");
   for(int i=0; i<cr_no; i++) {
      coset_reps.push_back(Matrix(cr_ptr, 4));
   }

   // Compute adjacency lists (keep track of pairs [edge label, coset reps])
   vector<vector<Matrix>> new_adj_lists;  // New adjacency lists (there should be a single element per list)
   vector<vector<int>> new_elabels;       // New edge labels (each is now: [coset rep1, coset rep2, a, b])
   // This is a long computation --> print some data to log
   log("Computing adjacency lists");
   log("oal_no", adj_no, "| cr_no", cr_no);

   int err_cnt=0, counter=0;     // err_cnt: # of lists with more than one element, counter: current edge no
   // Brace yourself for some loopin'!
   for(int edge=0; edge<oal.size(); edge++) { // Looping over adjacencies (p,q)
      cout << "Edge " << edge << "|" << flush; // Do not use util_io fncts
      for(int rep1=0; rep1<coset_reps.size(); rep1++) { // Looping over g_i
         cout << counter << "|" << flush;
         for(int rep2=0; rep2<coset_reps.size(); rep2++) { // Looping over g_j
            vector<Matrix> tmp;
            bool flag=false;  // Indicates if an element of this list has given a congruence subgroup element
            for(int witness=0; witness<oal[edge].size(); witness++) { // Looping over witnesses
               Matrix A(4);
               // L_{g_{i} p, g_{j} q} = g_{j}^{-1} * L{p,q} * g_{i}
               A = (coset_reps[rep2].inverse()) * oal[edge][witness] * coset_reps[rep1];
               if(A.mod3() == g_Id) {  // If A is in the congruence subgroup
                  tmp.push_back(A);
                  if(flag) {
                     narrator("ERROR: multiple elements in one adjacency list.", edge, rep1, rep2, witness);
                     err_cnt++;
                  }
                  flag=true;
               }
            } // END witnesses
            if(flag) { 
               counter++;
               cout << "+";
            } else {
               cout << ".";
            }
            new_adj_lists.push_back(tmp);
            new_elabels.push_back({rep1, rep2, elabels[edge][0], elabels[edge][1]});
         } // END g_j
      } // END g_i
      cout << endl;
   } // END adjacencies
   log("Found", new_adj_lists.size(), "edges,", counter, "non-empty,", err_cnt, "with more than one element");

   // Print everything to file (F_ofile)
   log("Writing to file");
   narrator("Writing to file");

   F_ofile << counter << endl;
   for(int i=0; i<new_adj_lists.size(); i++) {
      // Ignore empty lists
      if(new_adj_lists[i].size() == 0) continue;
      // Print header (i, rep1, rep2, a, b)
      F_ofile << i << " " 
              << new_adj_lists[i].size() << " "
              << new_elabels[i][0] << " "
              << new_elabels[i][1] << " "
              << new_elabels[i][2] << " "
              << new_elabels[i][3] << endl;
      for(int j=0; j<new_adj_lists[i].size(); j++) {
         new_adj_lists[i][j].print(F_ofile);
      }
      F_ofile << endl;
   }
}

// Parallel computing
void par_compute_adjacency_lists(ifstream& cr_ptr, ifstream& oal_ptr) {
   // Retrieve old adjacency lists
   vector<vector<Matrix>> oal;   // Witnesses of adjacency: one list for each adjacency 
   vector<vector<int>> elabels;  // Edge labels: vector of pairs (a, b)
   int adj_no;                   // Number of adjacency lists

   oal_ptr >> adj_no;
   debug("compute_adjacency_lists", "Reading", adj_no, "lists");

   for(int i=0; i<adj_no; i++) {
      int a,b,witness_no;        // witness_no: number of witnesses
      vector<Matrix> witness_list;
      oal_ptr >> a >> b >> witness_no;
      elabels.push_back({a, b});
      debug("compute_adjacency_lists", "Edge label:", a, b);
      
      for(int j=0; j<witness_no; j++) {
         witness_list.push_back(Matrix(oal_ptr, 4));
      }
      oal.push_back(witness_list);
   }

   // Retrieve coset representatives
   vector<Matrix> coset_reps;    // Coset representatives
   int cr_no;                    // Number of coset representatives

   cr_ptr >> cr_no;
   debug("compute_adjacency_lists", "Reading", cr_no, "coset representatives");
   for(int i=0; i<cr_no; i++) {
      coset_reps.push_back(Matrix(cr_ptr, 4));
   }

   // PARALLEL SECTION
   // =====================================================================================

   // Fork

   // Compute adjacency lists (keep track of pairs [edge label, coset reps])
   vector<vector<Matrix>> new_adj_lists;  // New adjacency lists (there should be a single element per list)
   vector<vector<int>> new_elabels;       // New edge labels (each is now: [coset rep1, coset rep2, a, b])
   // This is a long computation --> print some data to log
   log("Computing adjacency lists");
   log("oal_no", adj_no, "| cr_no", cr_no);

   int err_cnt=0, counter=0;     // err_cnt: # of lists with more than one element, counter: current edge no
   // Brace yourself for some loopin'!
   for(int edge=0; edge<oal.size(); edge++) { // Looping over adjacencies (p,q)
      cout << "Edge " << edge << "|" << flush; // Do not use util_io fncts
      for(int rep1=0; rep1<coset_reps.size(); rep1++) { // Looping over g_i
         cout << counter << "|" << flush;
         for(int rep2=0; rep2<coset_reps.size(); rep2++) { // Looping over g_j
            vector<Matrix> tmp;
            bool flag=false;  // Indicates if an element of this list has given a congruence subgroup element
            for(int witness=0; witness<oal[edge].size(); witness++) { // Looping over witnesses
               Matrix A(4);
               // L_{g_{i} p, g_{j} q} = g_{j}^{-1} * L{p,q} * g_{i}
               A = (coset_reps[rep2].inverse()) * oal[edge][witness] * coset_reps[rep1];
               if(A.mod3() == g_Id) {  // If A is in the congruence subgroup
                  tmp.push_back(A);
                  if(flag) {
                     narrator("ERROR: multiple elements in one adjacency list.", edge, rep1, rep2, witness);
                     err_cnt++;
                  }
                  flag=true;
               }
            } // END witnesses
            if(flag) { 
               counter++;
               cout << "+";
            } else {
               cout << ".";
            }
            new_adj_lists.push_back(tmp);
            new_elabels.push_back({rep1, rep2, elabels[edge][0], elabels[edge][1]});
         } // END g_j
      } // END g_i
      cout << endl;
   } // END adjacencies

   // Join all

   // =====================================================================================


   log("Found", new_adj_lists.size(), "edges,", counter, "non-empty,", err_cnt, "with more than one element");
   // Print everything to file (F_ofile)
   log("Writing to file");
   narrator("Writing to file");

   F_ofile << counter << endl;
   for(int i=0; i<new_adj_lists.size(); i++) {
      // Ignore empty lists
      if(new_adj_lists[i].size() == 0) continue;
      // Print header (i, rep1, rep2, a, b)
      F_ofile << i << " " 
              << new_adj_lists[i].size() << " "
              << new_elabels[i][0] << " "
              << new_elabels[i][1] << " "
              << new_elabels[i][2] << " "
              << new_elabels[i][3] << endl;
      for(int j=0; j<new_adj_lists[i].size(); j++) {
         new_adj_lists[i][j].print(F_ofile);
      }
      F_ofile << endl;
   }
}
