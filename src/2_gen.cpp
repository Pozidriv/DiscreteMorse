#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _2GEN
#define _2GEN
#include "2_gen.h"
#endif

// generate_matrices: generates matrices in the full group (within a radius of the identity)
// arguments:
//    - A
//    - B
//    - a inverse of A
//    - b inverse of B
//    - wordA, word for A
//    - wordB, word for B
//    - worda, word for inverse of A
//    - wordb, word for inverse of B
//    - elements Matrix vector in which the generated matrices are to be returned
//               This vector already has values and at each step we generate from them
//               !!WARNING!! Expecting this to be non-empty to start with (at least Id)
//    - words the words in A, B, a, b that each matrix represents
//    - radius number of steps to performed
// return value: pair of
//    - Matrix vector : the quotient elements that were generated
//    - string vector : the corresponding words
void generate_matrices(Matrix &A, Matrix &B, Matrix &a, Matrix &b, 
                       string wordA, string wordB, string worda, string wordb,
                       vector<Matrix> &elements, vector<string>& words, int radius);

// lowercase: helper function to convert an uppercase string to a lowercase one.
string lowercase(string);

// inList : helper function to check if a Matrix is already present in a list of matrices
// OPTIMIZATION: consider using a hash table to avoid O(n^2) runtime
bool inList(Matrix A, vector<Matrix> &list);

// Facade function: computes the quotient elements and words making them.
// Computes coset representatives and writes them in coset_reps
void two_gen(vector<Matrix> &coset_reps, int expected_size) {
   vector<Matrix> quotient_elements;
   quotient_elements.push_back(g_Id);
   vector<string> words;
   words.push_back("");

   // Loop over available generators until the whole group mod3 is generated
   int iter=1;
   while(iter<=I_MAX_GEN && quotient_elements.size() < expected_size) {
      // Setup
      ifstream gen1_ptr, gen2_ptr;
      gen1_ptr.open(DATA_GENERATORS[0], ifstream::in);
      gen2_ptr.open(DATA_GENERATORS[iter], ifstream::in);
      string wordA = "A", wordB; // the first generator is fixed I guess
      char b = 65 + iter; // 65 is A
      wordB.push_back(b);
      Matrix A(gen1_ptr, 4), B(gen2_ptr, 4);
      
      // Computation
      two_gen(A, B, wordA, wordB, quotient_elements, words, expected_size);

      // End step script
      debug("two_gen", "Quotient elements:", quotient_elements.size());
      iter++;
      gen1_ptr.close();
      gen2_ptr.close();
   }

   // Check for duplicates

   // Retrieve all generators
   vector<Matrix> generators;
   for(int i=0; i<I_MAX_GEN; i++) {
      ifstream tmp;
      tmp.open(DATA_GENERATORS[i], ifstream::in);
      Matrix M(tmp, 4);
      generators.push_back(M);
   }

   // Generate the actual coset representatives
   for(int i=0; i<quotient_elements.size(); i++) {
      Matrix my_matrix(4);
      my_matrix = g_Id;
      
      // Iteratively multiply by elements described by the word
      for(int j=0; j<words[i].size(); j++) {
         string switch_char = words[i].substr(j, 1);
         Matrix switch_matrix(4);
         char ting = switch_char.at(0);
         debug("two_gen","char", ting);
         if(switch_char == lowercase(switch_char)) { // lowercase -> inverse
            switch_matrix = generators[ting - 97].inverse();
            debug("two_gen","lowercase");
         } else { // uppercase -> normal
            switch_matrix = generators[ting - 65];
            debug("two_gen","uppercase");
         }
         my_matrix = my_matrix * switch_matrix;
         debug("two_gen","Switch:");
         //switch_matrix.print();
         debug("two_gen","Matrix:");
         //my_matrix.print();
      }
      // Check the matrix does indeed reduce to what it should mod 3.
      if(!(my_matrix.mod3() == quotient_elements[i])) {
         cout << "Houston, we've got a problem..." << endl;
         my_matrix.mod3().print();
         cout << "Expected" << endl;
         quotient_elements[i].print();
      }
      coset_reps.push_back(my_matrix);
   }
}

// WordA, WordB need to be uppercase
void two_gen(Matrix A, Matrix B, string wordA, string wordB, 
             vector<Matrix> &quotient_elements, vector<string> &words, int expected_size) {
   debug("two_gen", "Generating subgroup elements");
   A.print();
   B.print();
   if(quotient_elements.size() == 0) {
      cout << "[WARNING:two_gen] Quotient elements is empty. Potential mistake?" << endl;
   }
   if(quotient_elements.size() != words.size()) {
      cout << "[WARNING:two_gen] Quotient elements/word count mismatch. Potential mistake?" << endl;
   }
   ifstream in_ptr;
   in_ptr.open(ID_FILE, ifstream::in);
   // Reduced generators
   // ra, rb are inverses
   Matrix rA(4), rB(4), ra(4), rb(4), Id(in_ptr, 4); 
   string worda, wordb;

   rA = A;
   rB = B;
   ra = A.inverse();
   rb = B.inverse();
   worda = lowercase(wordA);
   wordb = lowercase(wordB);

   generate_matrices(rA, rB, ra, rb, wordA, wordB, worda, wordb, quotient_elements, words, 20);

}

void generate_matrices(Matrix &A, Matrix &B, Matrix &a, Matrix &b,
                       string wordA, string wordB, string worda, string wordb,
                       vector<Matrix> &elements, vector<string>& words, int radius) {
   //cout << "[DEBUG:generate_matrices] Running for " << radius << " steps" << endl;
//    - current current step number
//    - index ignore entries before this integer, they have been expanded already
   int index=0, tmp=0, size=1;

   for(int i=0; i<radius; i++) {
/*
      cout << "[DEBUG:generate_matrices] Step #" << i 
           << ". Current # of elements: " << elements.size() << endl;
      cout << "[DEBUG:generate_matrices] Starting index: " << index << endl;
*/      
      if(elements.size() == index) {
         debug("generate_matrices", "We're done. Exiting");
         return;
      }
      size = elements.size(); // elements.size() will change
      for(int j=index; j<size; j++) {
         //cout << "[DEBUG:generate_matrices] Computing elements to add to list" << endl;
         debug("generate_matrices", "Lvl", i, "| no:", elements.size());
         Matrix TA(4), TB(4), Ta(4), Tb(4), zero(4);

         TA = elements[j] * A;
         TB = elements[j] * B;
         Ta = elements[j] * a;
         Tb = elements[j] * b;

         TA = TA.mod3();
         TB = TB.mod3();
         Ta = Ta.mod3();
         Tb = Tb.mod3();

         if(TA == zero || TB == zero || Ta == zero || Tb == zero) {
            cout << "[WARNING:generate_matrices] Got zero matrix. Potential problem?" << endl;
         }
         if(!inList(TA, elements)) {
            elements.push_back(TA);
            words.push_back(words[j] + wordA);
         }

         if(!inList(TB, elements)) {
            elements.push_back(TB);
            words.push_back(words[j] + wordB);
         }

         if(!inList(Ta, elements)) {
            elements.push_back(Ta);
            words.push_back(words[j] + worda);
         }

         if(!inList(Tb, elements)) {
            elements.push_back(Tb);
            words.push_back(words[j] + wordb);
         }
//         cout << endl;
      }
      index = tmp;               // Update index
      tmp = elements.size();     // Store the current number of elements
   }

}

bool inList(Matrix A, vector<Matrix> &list) {
   for(int i=list.size()-1; i>-1; i--) {
      if(A == list[i]) {
         debug("two_gen|inList", "Found elt, index", i);
//         cout << i << " ";
         return true;
      }
   }
   return false;
}

string lowercase(string str) {
   string out = str;
   for(char &c: out) {
      c = tolower(c);
   }
   return out;
}
