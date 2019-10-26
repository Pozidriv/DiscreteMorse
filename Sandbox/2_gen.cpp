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

#define ID_FILE "Data/4x4Id.txt"

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

void two_gen(Matrix A, Matrix B, string wordA, string wordB, 
             vector<Matrix> &quotient_elements, vector<string> &words, int expected_size) {
   cout << "[DEBUG:two_gen] Generating subgroup elements" << endl;
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
   rA = B.inverse();
   worda = lowercase(wordA);
   wordb = lowercase(wordB);

   generate_matrices(rA, rB, ra, rb, wordA, wordB, worda, wordb, quotient_elements, words, 10);

}

void generate_matrices(Matrix &A, Matrix &B, Matrix &a, Matrix &b,
                       string wordA, string wordB, string worda, string wordb,
                       vector<Matrix> &elements, vector<string>& words, int radius) {
   //cout << "[DEBUG:generate_matrices] Running for " << radius << " steps" << endl;
//    - current current step number
//    - index ignore entries before this integer, they have been expanded already
   int current=0, index=0, tmp=0;

   for(int i=0; i<radius; i++) {
      cout << "[DEBUG:generate_matrices] Step #" << i 
           << ". Current # of elements: " << elements.size() << endl;
      cout << "[DEBUG:generate_matrices] Starting index: " << index << endl;
      
      if(elements.size() == index) {
         cout << "[DEBUG:generate_matrices] We're done. Exiting" << endl;
         return;
      }
      for(int j=index; j<elements.size(); j++) {
         //cout << "[DEBUG:generate_matrices] Computing elements to add to list" << endl;
         Matrix TA(4), TB(4), Ta(4), Tb(4);

         TA = elements[j] * A;
         TB = elements[j] * B;
         Ta = elements[j] * a;
         Tb = elements[j] * b;

         TA = TA.mod3();
         TB = TB.mod3();
         Ta = Ta.mod3();
         Tb = Tb.mod3();

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
         //cout << endl;
      }
      index = tmp;               // Update index
      tmp = elements.size();     // Store the current number of elements
   }

}

bool inList(Matrix A, vector<Matrix> &list) {
   for(int i=list.size()-1; i>-1; i--) {
      if(A == list[i]) {
         //cout << "[DEBUG:inList] Found element, index " << i << endl;
         //cout << i << " ";
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
