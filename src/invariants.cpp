#ifndef _INVARIANTS
#define _INVARIANTS
#include "invariants.h"
#endif

using namespace std;

int count_triangles(vector<Node<int>> G) {
   debug("count_triangles", "Yo mama");
   int count=0, triples=0;
   for(int i=0; i<G.size(); i++) {
      debug("count_triangles", i);
      Node<int> a = G[i];
      int vertexc=0;
      for(int j=0; j<a.edge_ptrs.size(); j++) {
         Node<int> b = G[a.edge_ptrs[j]];
         if(a.edge_ptrs[j] == i) continue;
         for(int k=0; k<b.edge_ptrs.size(); k++) {
            triples++;
            Node<int> c = G[b.edge_ptrs[k]];
            if(b.edge_ptrs[k] == a.edge_ptrs[j] || b.edge_ptrs[k] == i) continue;
            for(int l=0; l<c.edge_ptrs.size(); l++) {
               if(i == c.edge_ptrs[l]) {
                  count++;
                  vertexc++;
                  //narrator(i, a.edge_ptrs[j], b.edge_ptrs[k], c.edge_ptrs[l]);
               }
            }  // END l loop
         }  // END k loop
      }  // END j loop
      cout << " " << vertexc << " ";
   }  // END i loop
   debug("count_triangles", "Triples encountered:", triples);
   return count;
}
