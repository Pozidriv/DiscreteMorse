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
   options = { "k_gen" };
   ofstream log_ptr;
   log_ptr.open("Out/log.txt", ofstream::out);

   for(int i=0; i<argc; i++) {
      arguments[i] = argv[i];
   }

   if((arguments.size() >= 2) && arguments[1] == "k_gen") { // k_gen
      if(arguments.size() < 3) {
         cout << "Unspecified k. Exiting" << endl;
         exit(-1);
      }
      if(!is_int(arguments[2]) || stoi(arguments[2]) <= 0) {
         cout << "Unexpected value for k. Exiting" << endl;
         exit(-1);
      }

      int k = stoi(arguments[2]);
      int expected_size = 1152;
      log(log_ptr, "Generating a subgroup using", arguments[2], "elements");

      ifstream gen1_ptr, gen2_ptr, id_ptr;
      ofstream write_ptr;
      id_ptr.open(ID_FILE, ifstream::in);
      Matrix Id(id_ptr, 4);
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
         quotient_elements[i].print(write_ptr);
         write_ptr << endl;
      }

   } else { // If no option is matched
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
   }

   return 0;
}

bool is_int(const string &str) {
   if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+') ) ) 
      return false;

   char *p;
   strtol(str.c_str(), &p, 10); // Expecting integers to have at most 10 digits

   return (*p == 0);
}
