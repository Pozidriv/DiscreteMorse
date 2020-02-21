#ifndef _GRAPH
#define _GRAPH
#include "graph.h"
#endif
using namespace std;

template<>
Node<int>::Node(int i) 
   : neighbors(vector<Node<T>&>())
   , edge_ptrs(vector<int>())
   , value(i)
{ }

template<>
vector<Node<int>>& Node<int>::graph_from_edges(int n, vector<vector<int>> elabels) {
   vector<Node<int>> ret(*(new vector<Node<int>>()));
   for(int i=0; i<n; i++) { // Adding vertices
      ret.pushback(Node(i));
   }
   for(int i=0; i<elabels.size(); i++) {  // Adding edges
      ret[elabels[0]].edge_ptrs.push_back(elabels[1]);
      ret[elabels[1]].edge_ptrs.push_back(elabels[0]);
   }
   return ret;
}
