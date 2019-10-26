#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif
#ifndef _SANITY_CHECKS
#define _SANITY_CHECKS
#include "sanity_checks.h"
#endif

#define ID_FILE "Data/4x4Id.txt"

int check_order(Matrix &A) {
   int order=1;
   ifstream in_ptr;
   in_ptr.open(ID_FILE, ifstream::in);
   Matrix M(4), Id(in_ptr, 4);
   M = A;
   while(!(M == Id)) {
      //M.print();
      order++;
      M = A*M;
      M = M.mod3();
      if(order > 2000) {
         cout << "Houston, we've had a problem here." << endl;
         exit(-1);
      }
   }
   return order;
}
