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

int find(vector<int>& list, int v) {
   for(int i=0; i<list.size(); i++) {
      if(v==list[i]) return i;
   }
   return -1;
}

void graph_from_edges(int n, vector<vector<int>>& elabels, vector<Node<int>>& graph) {
   int pos;
   debug("graph_from_edges", "n", n);
   for(int i=0; i<n; i++) { // Adding vertices
      graph.push_back(Node<int>(i));
   }
   debug("graph_from_edges", "Finished making the graph");
   for(int i=0; i<elabels.size(); i++) {  // Adding edges
      //debug("graph_from_edges", i, n, "| pair", elabels[i][0], elabels[i][1]);
      const int a = elabels[i][0], b = elabels[i][1];
      pos = find(graph[a].edge_ptrs, b);
      if(pos == -1) {
         graph[a].edge_ptrs.push_back(b);
      }
      pos = find(graph[b].edge_ptrs, a);
      if(pos == -1) {
         graph[b].edge_ptrs.push_back(a);
      }
   }
}

void print(ostream& out, vector<Node<int>>& graph) {
   out << graph.size() << endl;
   for(int i=0; i<graph.size(); i++) {
      out << i << ":";
      for(int j=0; j<graph[i].edge_ptrs.size(); j++) {
         out << graph[i].edge_ptrs[j] << " ";
      }
      out << endl;
   }
}
