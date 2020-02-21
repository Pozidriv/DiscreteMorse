// 12/02/2020
// An adjacency list implementation of a graph
//
#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
using namespace std;

//
template<class T>
class Node {
   public:
      T value;
      vector<int> neighbors; // Store the indices of your neighbors

      // CONSTRUCTORS
      // Make your own constructor for your favorite type
      Node();
};

// T is the type of the node values
template<class T>
class Graph {
   public:
      vector<Node<T>> vertices;
      vector<vector<int>> adj_lists;
      int size; // number of nodes


      // METHODS

      void print(ofstream&);        // Print to file
      void print();                 // Print to file (default)

      // CONSTRUCTORS
      
      Graph();                      // Default constructor
      Graph(int);                   // Creates empty graph of specified size
      //Graph(ifstream&, int);        // Construct from file input

      // OPERATOR OVERLOADING
};
