// (18/08/2019)
// Toolbox for matrix operations
//
#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
using namespace std;


// Class for integer entried matrices
// Since we work with square matrices, most methods expect square matrices
//
class Matrix {
   public:
      vector<vector<long int> > entries;
      int rows, cols;


      // METHODS

      Matrix transpose(void);       // Compute matrix tranpose
      Matrix inverse(void);         // Compute 4x4 matrix inverse (of an invertible matrix)
      //Matrix mult(Matrix);        // Multiply two matrices
      //bool equal(Matrix);         // Check entrywise equality
      Matrix mod3(void);            // Reduce mod3 entrywise
      int det(void);                // Compute 4x4 determinant 
      Matrix submatrix(int,int);    // Submatrix 

      void print(ofstream&);        // Print to file
      void print();                 // Print to file (default)

      // CONSTRUCTORS
      
      Matrix();                     // Default constructor
      Matrix(int);                  // Creates empty square matrix of specified size
      Matrix(int,int);              // Creates empty nxk matrix
      Matrix(ifstream&, int);       // Construct from file input
      Matrix(Matrix,int,int);       // Submatrix constructor

      // OPERATOR OVERLOADING

      Matrix operator+ (const Matrix&);
      Matrix operator- (const Matrix&);
      Matrix operator* (const Matrix&);
      Matrix& operator= (const Matrix&);
      bool operator== (const Matrix&);
};
