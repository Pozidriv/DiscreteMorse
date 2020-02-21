// (20/02/2020)
// Graph class, adjacency lists
//
#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _UTIL_IO
#define _UTIL_IO
#include "util_io.h"
#endif
using namespace std;

template<class T> 
class Node {
   public:
      vector<int> edge_ptrs;     // Pointer to edge elements (living in a global array)
      T value;

      // CONSTRUCTORS
      Node(int i);

      // METHODS
      // Implement tree traversals
};

template<class T> 
class Graph {
   public:
      vector<Node<T>&> vertices;
      // CONSTRUCTORS

      // METHODS
      // Implement tree traversals
};


void graph_from_edges(int n, vector<vector<int>>& elabels, vector<Node<int>>& graph);
