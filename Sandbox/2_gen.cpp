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
//    - elements Matrix vector in which the generated matrices are to be returned
//               This vector already has values and at each step we generate from them
//               !!WARNING!! Expecting this to be non-empty to start with (at least Id)
//    - words the words in A, B, a, b that each matrix represents
//    - radius number of steps to performed
vector<Matrix>& generate_matrices(Matrix &A, Matrix &B, Matrix &a, Matrix &b, 
                                  vector<Matrix> &elements, vector<string>& words, int radius);


// inList : helper function to check if a Matrix is already present in a list of matrices
bool inList(Matrix A, vector<Matrix> &list);

vector<Matrix>& two_gen(Matrix A, Matrix B, vector<Matrix> &quotient_elements, int expected_size) {
   ifstream in_ptr;
   in_ptr.open(ID_FILE, ifstream::in);
   // Reduced generators
   // ra, rb are inverses
   Matrix rA(4), rB(4), ra(4), rb(4), Id(in_ptr, 4); 

   // words corresponding to the matrices that will be produced
   vector<string> words;
   words.push_back("");

   rA = A;
   rB = B;
   ra = A.inverse();
   rA = B.inverse();


   generate_matrices(rA, rB, ra, rb, quotient_elements, words, 5);

   return quotient_elements;
}

vector<Matrix>& generate_matrices(Matrix &A, Matrix &B, Matrix &a, Matrix &b, 
                                  vector<Matrix> &elements, vector<string>& words, int radius) {
//    - current current step number
//    - index ignore entries before this integer, they have been expanded already
   int current=0, index=1, tmp;

   for(int i=0; i<radius; i++) {
      for(int j=index; j<elements.size(); j++) {
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
            words.push_back(words[j] + "A");
         }

         if(!inList(TB, elements)) {
            elements.push_back(TB);
            words.push_back(words[j] + "B");
         }

         if(!inList(Ta, elements)) {
            elements.push_back(Ta);
            words.push_back(words[j] + "a");
         }

         if(!inList(Tb, elements)) {
            elements.push_back(Tb);
            words.push_back(words[j] + "b");
         }
      }
      index = tmp;               // Update index
      tmp = elements.size();     // Store the current number of elements
   }

   return elements;
}

bool inList(Matrix A, vector<Matrix> &list) {
   for(int i=list.size()-1; i>-1; i--) {
      if(A == list[i])
         return true;
   }
   return false;
}
