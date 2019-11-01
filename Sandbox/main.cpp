// (22/10/2019) Central file from which computations will be performed.

#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
#ifndef _2GEN
#define _2GEN
#include "2_gen.h"
#endif
#ifndef _SANITY_CHECKS
#define _SANITY_CHECKS
#include "sanity_checks.h"
#endif

#define ID_FILE "Data/4x4Id.txt"
#define OUT_FILE "Out/quotient_elements.txt"
#define COSET_REPS_FILE "Data/coset_reps_mod3.txt"
#define OLD_ADJ_LISTS_FILE "../Data/HypMan.txt"

#define KGEN "k_gen"
#define KGEC 1
#define CREPES "coset_reps"
#define CREPEC 2
#define ADJ_LISTS "adj_lists"
#define ADJ_LISTC 1

// helper functions to print
// !!! WARNING !!! Do not put the following at the end of the file.
// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
void log(ofstream& out_file);
template<typename First, typename ... Strings>
void log(ofstream& out_file, First arg, const Strings&... rest);

void log(ofstream& out_file) {
   cout << endl;
   out_file << endl;
}

template<typename First, typename ... Strings>
void log(ofstream& out_file, First arg, const Strings&... rest) {
   cout << arg << " ";
   out_file << arg << " ";
   log(out_file, rest...);
}
//*******************************************************************

// Helper function to test if a string is an int
bool is_int(const string&);

int main(int argc, char **argv) {
   vector<string> arguments(argc), options;
   options = { KGEN, CREPES, ADJ_LISTS }; // expected number of arguments for each option
   vector<int> optionc = { KGEC, CREPEC, ADJ_LISTC }; // expected number of arguments for each option
   ifstream id_ptr;
   ofstream log_ptr;
   log_ptr.open("Out/log.txt", ofstream::out);

   id_ptr.open(ID_FILE, ifstream::in);
   Matrix Id(id_ptr, 4);

   cout << "========= Running Main =========" << endl;

   for(int i=0; i<argc; i++) {
      arguments[i] = argv[i];
   }

   if(arguments.size() >= 2) {
      if(arguments[1] == KGEN) { // k_gen
         log(log_ptr, "K GEN");
         if(arguments.size()-2 != KGEC) {
            cout << "Unexpected arguments." << endl;
            cout << "Usage: run " << KGEC << " [number of generators]" << endl;
            cout << "Exiting" << endl;
            exit(-1);
         }
         if(!is_int(arguments[2]) || stoi(arguments[2]) <= 0) {
            cout << "Unexpected value for k. Exiting" << endl;
            exit(-1);
         }

         int k = stoi(arguments[2]);
         int expected_size = 720;
         log(log_ptr, "Generating a subgroup using", arguments[2], "elements");

         ifstream gen1_ptr, gen2_ptr;
         ofstream write_ptr;
         vector<Matrix> quotient_elements;
         vector<string> words;

         // Initialize things
         quotient_elements.push_back(Id);
         words.push_back("");

         for(int i=0; i<k/2; i++) {
            Matrix A(4), B(4);
            string wordA, wordB, gen_file1, gen_file2;
            stringstream tmp; // fml why do I have to do this?
            

            tmp << "Data/gen" << (2*(i+1))-1 << ".txt";
            gen_file1 = tmp.str();
            if((2*i) + 1 == k) { // if we have an odd number of generators, just replace the last one by the identity
               gen_file2 = ID_FILE;
            } else {
               tmp.str("");
               tmp.clear();
               tmp << "Data/gen" << (2*(i+1)) << ".txt";
               gen_file2 = tmp.str();
            }
            gen1_ptr.open(gen_file1, ifstream::in);
            gen2_ptr.open(gen_file2, ifstream::in);
            cout << gen_file1 << endl;
            cout << gen_file2 << endl;
            //log(log_ptr, i, "round generators filenames: ");
            //log(log_ptr, gen_file1, endl, gen_file2);

            A = Matrix(gen1_ptr, 4);
            B = Matrix(gen2_ptr, 4);
            char a,b;
            a = 65 + (2*i); // hopefully we're using ASCII? 
            b = 65 + (2*i) + 1;
            wordA.push_back(a);
            wordB.push_back(b);

            // Sanity check: check the order of the elements
            int order=0;
            order = check_order(A);
            log(log_ptr, 2*i, "generator order: ", order);
            order = check_order(B);
            log(log_ptr, (2*i +1) , "generator order: ", order);

            // Generate subgroup elements
            two_gen(A, B, wordA, wordB, quotient_elements, words, expected_size);
            log(log_ptr, "Quotient computed successfuly.");
            log(log_ptr, "Found", quotient_elements.size(), "elements.");

            // Close reading ptrs
            gen1_ptr.close();
            gen2_ptr.close();
         }

         log(log_ptr, "Writing to file", OUT_FILE);
         write_ptr.open(OUT_FILE, ofstream::out);
         for(int i=0; i<quotient_elements.size(); i++) {
            write_ptr << words[i] << endl;
            quotient_elements[i].print(write_ptr);
            write_ptr << endl;
         }
         return 0;
      }
//************************************************
      if(arguments[1] == CREPES) { // Generate coset representatives
         log(log_ptr, "COSET REPRESENTATIVES");
         if(arguments.size()-2 != CREPEC) {
            cout << "Unexpected arguments." << endl;
            cout << "Usage: run " << CREPEC << " [output file name] [expected number]" << endl;
            cout << "Exiting" << endl;
            exit(-1);
         }

         string filename = arguments[2];
         if(!is_int(arguments[3]) || stoi(arguments[3]) <= 0) {
            cout << "Unexpected value for expected number. Exiting" << endl;
            exit(-1);
         }
         int expected_size = stoi(arguments[3]);

         log(log_ptr, "Generating the coset representatives to file", arguments[2], ". Expecting size", arguments[3]);

         ifstream gen1_ptr, gen2_ptr;
         ofstream write_ptr;
         vector<Matrix> quotient_elements, generators;
         vector<string> words;

         // Initialize things
         quotient_elements.push_back(Id);
         words.push_back("");
         
         int iii=0, max_gen=8;
         while(iii<=max_gen && quotient_elements.size()<expected_size) {
            Matrix A(4), B(4);
            string wordA, wordB, gen_file1, gen_file2;
            stringstream tmp; // fml why do I have to do this?
            

            tmp << "Data/gen" << (2*(iii+1))-1 << ".txt";
            gen_file1 = tmp.str();
            // if we have an odd number of generators, just replace the last one by the identity
            if((2*iii) + 1 == max_gen) { 
               gen_file2 = ID_FILE;
            } else {
               tmp.str("");
               tmp.clear();
               tmp << "Data/gen" << (2*(iii+1)) << ".txt";
               gen_file2 = tmp.str();
            }
            gen1_ptr.open(gen_file1, ifstream::in);
            gen2_ptr.open(gen_file2, ifstream::in);
            cout << gen_file1 << endl;
            cout << gen_file2 << endl;
            //log(log_ptr, i, "round generators filenames: ");
            //log(log_ptr, gen_file1, endl, gen_file2);

            A = Matrix(gen1_ptr, 4);
            B = Matrix(gen2_ptr, 4);
            generators.push_back(A);
            generators.push_back(B);
            char a,b;
            a = 65 + (2*iii); // hopefully we're using ASCII? 
            b = 65 + (2*iii) + 1;
            wordA.push_back(a);
            wordB.push_back(b);

            // Sanity check: check the order of the elements
            int order=0;
            order = check_order(A);
            log(log_ptr, 2*iii, "generator order: ", order);
            order = check_order(B);
            log(log_ptr, (2*iii +1) , "generator order: ", order);

            // Generate subgroup elements
            two_gen(A, B, wordA, wordB, quotient_elements, words, expected_size);
            //log(log_ptr, "Quotient computed successfuly.");
            log(log_ptr, "Found", quotient_elements.size(), "elements.");

            // Close reading ptrs
            gen1_ptr.close();
            gen2_ptr.close();
            iii++; // Don't forget!!
         }

         cout << "================ Recovering coset representatives ================" << endl;

         log(log_ptr, "Writing quotient elements to file", OUT_FILE);
         write_ptr.open(OUT_FILE, ofstream::out);
         for(int i=0; i<quotient_elements.size(); i++) {
            write_ptr << words[i] << endl;
            quotient_elements[i].print(write_ptr);
            write_ptr << endl;
         }
         write_ptr.close();

         log(log_ptr, "Writing coset representatives to file", filename);
         write_ptr.open(filename, ofstream::out);
         write_ptr << words.size() << endl;
         for(int i=0; i<words.size(); i++) {
            Matrix A(4);
            A = Id;

            for(char &c: words[i]) {
               int index=0;
               // Two cases: either uppercase or lowercase
               if(c >= 65 && c <= 90) {         // Upper
                  index = c-65;
                  if(index >= generators.size()) {
                     log(log_ptr, "Generator", index, "could not be found");
                     exit(-1);
                  }
                  A = A*generators[index];
               } else if(c >= 97 && c <= 122) { // Lower
                  index = c-97;
                  if(index >= generators.size()) {
                     log(log_ptr, "Generator", index, "could not be found");
                     exit(-1);
                  }
                  A = A*(generators[index].inverse());
               } else {                         // Else ERROR
                  cout << "WTF" << endl;
                  exit(-1);
               }
            }
            A.print(write_ptr);
            write_ptr << endl;
         }
         write_ptr.close();

         return 0;
      }
//************************************************
      if(arguments[1] == ADJ_LISTS) { // Generate new adjacency lists
         log(log_ptr, "ADJACENCY LISTS");
         if(arguments.size()-2 != ADJ_LISTC) {
            cout << "Unexpected arguments." << endl;
            cout << "Usage: run " << ADJ_LISTC << " [output file name]" << endl;
            cout << "Exiting" << endl;
            exit(-1);
         }

         string filename = arguments[2];
         log(log_ptr, "Generating the new adjacency lists to file", arguments[2]);

         ifstream coset_reps_ptr, old_adj_lists_ptr;
         ofstream write_ptr;
         coset_reps_ptr.open(COSET_REPS_FILE, ifstream::in);
         old_adj_lists_ptr.open(OLD_ADJ_LISTS_FILE, ifstream::in);
         vector<Matrix> coset_reps;
         vector<vector<Matrix> > old_adj_lists, adj_lists;

         // Retrieve coset representatives from file  
         // Dependin on memory limitations we may want to combine this with the generation
         int n=0;
         coset_reps_ptr >> n;
         for(int i=0; i<n; i++) {
            Matrix A(coset_reps_ptr, 4);
            coset_reps.push_back(A);
         }

         log(log_ptr, "Retrieved", coset_reps.size(), "representatives from", COSET_REPS_FILE);
         
         // Retrieve old adjacency lists from file
         // RECALL FILE FORMAT :
         // [START]
         // m
         // {f1: m times}
         // a b
         // n
         // {f2: n times}
         // MATRIX
         // {f2}
         // {f1}
         // [END]
         //
         // (a,b) is the edge label
         int m=0,a=0,b=0;
         n=0;

         old_adj_lists_ptr >> m;
         for(int i=0; i<m; i++) {
            vector<Matrix> tmp;
            cout << ".";
            old_adj_lists_ptr >> a;
            old_adj_lists_ptr >> b;
            old_adj_lists_ptr >> n;

            for(int j=0; j<n; j++) {
               Matrix A(old_adj_lists_ptr, 4);
               tmp.push_back(A);
            }
            old_adj_lists.push_back(tmp);
         }
         cout << endl;

         log(log_ptr, "Retrieved", old_adj_lists.size(), "adjacency lists from", OLD_ADJ_LISTS_FILE);


         // Compute new adjacency lists
         // So many loops...
         int errcount=0, counter=0;
         log(log_ptr, "Computing adjacency lists");
         for(int edge=0; edge<old_adj_lists.size(); edge++) { // Looping over edges
         //for(int edge=0; edge<1; edge++) { // Looping over edges
            cout << "Edge " << edge << "| " << flush;
            for(int rep1=0; rep1<coset_reps.size(); rep1++) { // Looping over g_i
               cout << counter << " " << flush;
               for(int rep2=0; rep2<coset_reps.size(); rep2++) { // Looping over g_j
                  vector<Matrix> tmp;
                  bool flag=false;
                  for(int element=0; element<old_adj_lists[edge].size(); element++) {  // Looping over elements in list
                     Matrix A(4);
                     A = (coset_reps[rep2].inverse())*old_adj_lists[edge][element]*coset_reps[rep1];
                     if(A.mod3() == Id) { // If A is in congruence subgroup
                        tmp.push_back(A);
                        if(flag) {
                           cout << "[DEBUG] Error, multiple elements in one adjacency list" << endl;
                           errcount++;
                        }
                        flag=true;
                     }
                  }
                  if(flag) counter++;
                  adj_lists.push_back(tmp);
               }
            }
            cout << endl;
         }
         log(log_ptr, "Found", adj_lists.size(), "adjacency lists,", counter, "non-empty;", errcount, "with more than 1 element");

         
         log(log_ptr, "Writing adjacency lists to file", filename);
         write_ptr.open(filename, ofstream::out);
         write_ptr << adj_lists.size() << endl;
         for(int i=0; i<adj_lists.size(); i++) {
            // Ignore empty lists
            if(adj_lists[i].size() == 0) continue;
            write_ptr << adj_lists[i].size() << endl;
            for(int j=0; j<adj_lists[i].size(); j++) {
               adj_lists[i][j].print(write_ptr);
            }
            write_ptr << endl;
         }
         write_ptr.close();
         
         return 0;
      }
   }


//************************************************
   // If no option is matched
   cout << "Error: invalid arguments '";
   for(int i=0; i<arguments.size(); i++) {
      cout << arguments[i];
      if(i == arguments.size()-1)
         cout << "'" << endl;
      else
         cout << " ";
   }
   cout << "Usage: ./run [option]" << endl;
   cout << "Implemented options: ";
   for(int i=0; i<options.size(); i++) {
      cout << options[i];
      if(i<options.size()-1)
        cout << "|";
   }
   cout << endl;

   return 0;
}

bool is_int(const string &str) {
   if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+') ) ) 
      return false;

   char *p;
   strtol(str.c_str(), &p, 10); // Expecting integers to have at most 10 digits

   return (*p == 0);
}
