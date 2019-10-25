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

int main(int argc, char **argv) {
   vector<string> arguments(argc), options;
   options = { "2_gen" };

   for(int i=0; i<argc; i++) {
      arguments[i] = argv[i];
   }

   if(arguments[1] == "2_gen") { // 2_gen
      cout << "Generating a subgroup using 2 elements" << endl;
      string gen_file1, gen_file2;
      ifstream gen1_ptr, gen2_ptr;
      Matrix A, B;
      vector<Matrix> quotient_elements;
      int expected_size = 1152;

      gen_file1 = "Data/gen1.txt";
      gen_file2 = "Data/gen2.txt";
      gen1_ptr.open(gen_file1, ifstream::in);
      gen2_ptr.open(gen_file2, ifstream::in);

      A = Matrix(gen1_ptr, 4);
      B = Matrix(gen2_ptr, 4);

      two_gen(A, B, quotient_elements, expected_size);

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
