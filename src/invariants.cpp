#ifndef _INVARIANTS
#define _INVARIANTS
#include "invariants.h"
#endif

using namespace std;

int count_triangles(vector<Node<int>> G) {
   int count=0;
   for(int i=0; i<G.size(); i++) {
      Node<int> a = G[i];
      for(int j=0; j<a.edge_ptrs.size(); j++) {
         Node<int> b = G[a.edge_ptrs[j]];
         for(int k=0; k<b.edge_ptrs.size(); k++) {
            if(i == b.edge_ptrs[k]) {
               count++;
            }
         }  // END k loop
      }  // END j loop
   }  // END i loop
}
