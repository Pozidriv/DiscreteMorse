// (20/02/2020)
// Graph class, adjacency lists
//
#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
using namespace std;

template<class T> 
class Node {
   public:
      vector<Node<T>&> neighbors;
      vector<int> edge_ptrs;     // Pointer to edge elements (living in a global array)
      T value;

      // CONSTRUCTORS

      // METHODS
      // Implement tree traversals
};


template<>
vector<Node<int>>& Node<int>::graph_from_edges(int n, vector<vector<int>> elabels);
