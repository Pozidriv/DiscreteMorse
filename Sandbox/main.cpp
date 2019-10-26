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

int main(int argc, char **argv) {
   vector<string> arguments(argc), options;
   options = { "2_gen" };
   ofstream log_ptr;
   log_ptr.open("Out/log.txt", ofstream::out);

   for(int i=0; i<argc; i++) {
      arguments[i] = argv[i];
   }

   if((arguments.size() >= 2) && arguments[1] == "2_gen") { // 2_gen
      log(log_ptr, "Generating a subgroup using 2 elements");
      string gen_file1, gen_file2, gen_file3, gen_file4;
      ifstream gen1_ptr, gen2_ptr, gen3_ptr, gen4_ptr, id_ptr;
      ofstream write_ptr;

      id_ptr.open(ID_FILE, ifstream::in);
      Matrix A(4), B(4), C(4), D(4), Id(id_ptr, 4);
      string wordA, wordB, wordC, wordD;
      vector<Matrix> quotient_elements;
      vector<string> words;
      int expected_size = 1152;

      gen_file1 = "Data/gen1.txt";
      gen_file2 = "Data/gen2.txt";
      gen_file3 = "Data/gen3.txt";
      gen_file4 = "Data/gen4.txt";
      gen1_ptr.open(gen_file1, ifstream::in);
      gen2_ptr.open(gen_file2, ifstream::in);
      gen3_ptr.open(gen_file3, ifstream::in);
      gen4_ptr.open(gen_file4, ifstream::in);

      A = Matrix(gen1_ptr, 4);
      B = Matrix(gen2_ptr, 4);
      C = Matrix(gen3_ptr, 4);
      D = Matrix(gen4_ptr, 4);
      wordA = "A";
      wordB = "B";
      wordC = "C";
      wordD = "D";

      // Sanity check: check the order of the elements
      int order=0;
      order = check_order(A);
      log(log_ptr, "First generator order: ", order);
      order = check_order(B);
      log(log_ptr, "Second generator order: ", order);
      order = check_order(C);
      log(log_ptr, "Third generator order: ", order);
      order = check_order(D);
      log(log_ptr, "Fourth generator order: ", order);

      // Generate subgroup elements
      quotient_elements.push_back(Id);
      words.push_back("");
      two_gen(A, B, wordA, wordB, quotient_elements, words, expected_size);
      log(log_ptr, "Quotient computed successfuly.");
      log(log_ptr, "Found", quotient_elements.size(), "elements.");

      log(log_ptr, "Trying with new generators");
      two_gen(C, D, wordC, wordD, quotient_elements, words, expected_size);
      log(log_ptr, "Found", quotient_elements.size(), "elements.");
      

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
