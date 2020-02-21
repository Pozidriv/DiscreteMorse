#ifndef _GRAPH
#define _GRAPH
#include "graph.h"
#endif
using namespace std;

template<>
Node<int>::Node(int i) 
   : edge_ptrs(vector<int>())
   , value(i)
{ }

void graph_from_edges(int n, vector<vector<int>>& elabels, vector<Node<int>>& graph) {
   debug("graph_from_edges", "n", n);
   for(int i=0; i<n; i++) { // Adding vertices
      graph.push_back(Node<int>(i));
   }
   debug("graph_from_edges", "Finished making the graph");
   for(int i=0; i<elabels.size(); i++) {  // Adding edges
      //debug("graph_from_edges", i, n, "| pair", elabels[i][0], elabels[i][1]);
      graph[elabels[i][0]].edge_ptrs.push_back(elabels[i][1]);
      graph[elabels[i][1]].edge_ptrs.push_back(elabels[i][0]);
   }
}
