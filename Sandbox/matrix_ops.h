// (18/08/2019)
// Toolbox for matrix operations
//
#include <bits/stdc++.h>
using namespace std;

#define VERBOSE 0

// Class for integer entried matrices
// Since we work with square matrices, most methods expect square matrices
//
class Matrix {
   public:
      vector<vector<long int> > entries;
      int rows, cols;


      // METHODS

      Matrix transpose(void); // Compute matrix tranpose
      Matrix inverse(void);   // Compute 4x4 matrix inverse (of an invertible matrix)
      //Matrix mult(Matrix);    // Multiply two matrices
      //bool equal(Matrix);     // Check entrywise equality
      Matrix mod3(void);      // Reduce mod3 entrywise

      void print(ofstream&);   // Print to file
      void print();   // Print to file

      // CONSTRUCTORS
      
      Matrix();                // Default constructor
      Matrix(int);             // Creates empty square matrix of specified size
      Matrix(int,int);         // Creates empty nxk matrix
      Matrix(ifstream&, int);   // Construct from file input

      // OPERATOR OVERLOADING

      Matrix operator+ (const Matrix&);
      Matrix operator- (const Matrix&);
      Matrix operator* (const Matrix&);
      bool operator== (const Matrix&);
};

// ************************* CONSTRUCTORS ********************************

// Standard constructor
Matrix::Matrix() {
}

// Empty square matrix constructor
Matrix::Matrix(int n) {
   if(n<=0) {
      cout << "[Matrix] Error, expected positive dimensions" << endl;
      exit(-1);
   }
   rows = n; cols = n;
   entries = vector<vector<long int> >(n, vector<long int>(n));
}

// Empty nxk matrix constructor
// n : number of rows
// k : number of columns
Matrix::Matrix(int n, int k) {
   if(n<=0 || k<=0) {
      cout << "[Matrix] Error, expected positive dimensions" << endl;
      exit(-1);
   }
   rows = n; cols = k;
   entries = vector<vector<long int> >(n, vector<long int>(k));
}

// File input constructor
// Expected input: 
// - square matrix of dimension n
// - space/newline separated string of integers
// - full 1st row, then full 2nd row, etc...
Matrix::Matrix(ifstream &str, int n) {
   if(n<=0) {
      cout << "[Matrix] Error, expected positive dimensions" << endl;
      exit(-1);
   }
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Constructing matrix from file" << endl;
   }

   rows = n; cols = n;
   entries = vector<vector<long int> >(n, vector<long int>(n));
   for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
         str >> entries[i][j];
      }
   }
}

// ************************ OPERATORS ********************************

bool Matrix::operator==(const Matrix &B) {     // Check entrywise equality
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Checking matrix equality" << endl;
   }

   if(B.rows!=rows || B.cols!=cols) {
      if(VERBOSE==1) {
         cout << "[Matrix:operator==] Matrix dimension mismatch. Potential problem?" << endl;
      }
      return false;
   }
   int flag=0;
   for(int i=0; i<rows; i++) {
       for(int j=0; j<cols; j++) {
           if(entries[i][j] != B.entries[i][j])
               flag = 1;
       }
   }
   return !flag;
}

Matrix Matrix::operator+(const Matrix &M) {
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Adding matrices" << endl;
   }
   if(M.rows!=rows || M.cols!=cols) {
      if(VERBOSE==1) {
         cout << "[Matrix:operator+] Matrix dimension mismatch. Exiting" << endl;
      }
      exit(-1);
   }

   Matrix A(rows,cols);
   for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
          A.entries[i][j] = entries[i][j] + M.entries[i][j];
      }
   }

   return A;
}

Matrix Matrix::operator-(const Matrix &M) {
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Substracting matrices" << endl;
   }

   if(M.rows!=rows || M.cols!=cols) {
      if(VERBOSE==1) {
         cout << "[Matrix:operator-] Matrix dimension mismatch. Exiting" << endl;
      }
      exit(-1);
   }

   Matrix A(rows,cols);
   for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
          A.entries[i][j] = entries[i][j] - M.entries[i][j];
      }
   }

   return A;
}

Matrix Matrix::operator*(const Matrix &M) {
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Multipying matrices" << endl;
   }

   if(M.cols!=rows || M.rows!=cols) {
      if(VERBOSE==1) {
         cout << "[Matrix:operator*] Matrix dimension mismatch. Exiting" << endl;
      }
      exit(-1);
   }

   Matrix A(rows,cols);
   for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
         long int sum=0;
         for(int k=0; k<cols; k++) {
            sum += entries[i][k] * M.entries[k][j];
         }
         A.entries[i][j] = sum;
      }
   }

   return A;
}

// ************************* METHODS ********************************

// Compute matrix tranpose
Matrix Matrix::transpose(void) {
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Computing matrix transpose" << endl;
   }
   Matrix A(cols, rows);

   for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
         A.entries[j][i] = entries[i][j];
      }
   }

   return A;
} 

// Compute 4x4 matrix inverse
// Expects 4x4 invertible matrix as input
Matrix Matrix::inverse(void) {   // Compute 4x4 matrix inverse (of an invertible matrix)
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Computing matrix inverse" << endl;
   }
   Matrix inv(4,4);

   inv.entries[0][0] = entries[1][1]  * entries[2][2] * entries[3][3] - 
            entries[1][1]  * entries[2][3] * entries[3][2] - 
            entries[2][1]  * entries[1][2]  * entries[3][3] + 
            entries[2][1]  * entries[1][3]  * entries[3][2] +
            entries[3][1] * entries[1][2]  * entries[2][3] - 
            entries[3][1] * entries[1][3]  * entries[2][2];

   inv.entries[1][0] = -entries[1][0]  * entries[2][2] * entries[3][3] + 
             entries[1][0]  * entries[2][3] * entries[3][2] + 
             entries[2][0]  * entries[1][2]  * entries[3][3] - 
             entries[2][0]  * entries[1][3]  * entries[3][2] - 
             entries[3][0] * entries[1][2]  * entries[2][3] + 
             entries[3][0] * entries[1][3]  * entries[2][2];

   inv.entries[2][0] = entries[1][0]  * entries[2][1] * entries[3][3] - 
            entries[1][0]  * entries[2][3] * entries[3][1] - 
            entries[2][0]  * entries[1][1] * entries[3][3] + 
            entries[2][0]  * entries[1][3] * entries[3][1] + 
            entries[3][0] * entries[1][1] * entries[2][3] - 
            entries[3][0] * entries[1][3] * entries[2][1];

   inv.entries[3][0] = -entries[1][0]  * entries[2][1] * entries[3][2] + 
              entries[1][0]  * entries[2][2] * entries[3][1] +
              entries[2][0]  * entries[1][1] * entries[3][2] - 
              entries[2][0]  * entries[1][2] * entries[3][1] - 
              entries[3][0] * entries[1][1] * entries[2][2] + 
              entries[3][0] * entries[1][2] * entries[2][1];

   inv.entries[0][1] = -entries[0][1]  * entries[2][2] * entries[3][3] + 
             entries[0][1]  * entries[2][3] * entries[3][2] + 
             entries[2][1]  * entries[0][2] * entries[3][3] - 
             entries[2][1]  * entries[0][3] * entries[3][2] - 
             entries[3][1] * entries[0][2] * entries[2][3] + 
             entries[3][1] * entries[0][3] * entries[2][2];

   inv.entries[1][1] = entries[0][0]  * entries[2][2] * entries[3][3] - 
            entries[0][0]  * entries[2][3] * entries[3][2] - 
            entries[2][0]  * entries[0][2] * entries[3][3] + 
            entries[2][0]  * entries[0][3] * entries[3][2] + 
            entries[3][0] * entries[0][2] * entries[2][3] - 
            entries[3][0] * entries[0][3] * entries[2][2];

   inv.entries[2][1] = -entries[0][0]  * entries[2][1] * entries[3][3] + 
             entries[0][0]  * entries[2][3] * entries[3][1] + 
             entries[2][0]  * entries[0][1] * entries[3][3] - 
             entries[2][0]  * entries[0][3] * entries[3][1] - 
             entries[3][0] * entries[0][1] * entries[2][3] + 
             entries[3][0] * entries[0][3] * entries[2][1];

   inv.entries[3][1] = entries[0][0]  * entries[2][1] * entries[3][2] - 
             entries[0][0]  * entries[2][2] * entries[3][1] - 
             entries[2][0]  * entries[0][1] * entries[3][2] + 
             entries[2][0]  * entries[0][2] * entries[3][1] + 
             entries[3][0] * entries[0][1] * entries[2][2] - 
             entries[3][0] * entries[0][2] * entries[2][1];

   inv.entries[0][2] = entries[0][1]  * entries[1][2] * entries[3][3] - 
            entries[0][1]  * entries[1][3] * entries[3][2] - 
            entries[1][1]  * entries[0][2] * entries[3][3] + 
            entries[1][1]  * entries[0][3] * entries[3][2] + 
            entries[3][1] * entries[0][2] * entries[1][3] - 
            entries[3][1] * entries[0][3] * entries[1][2];

   inv.entries[1][2] = -entries[0][0]  * entries[1][2] * entries[3][3] + 
             entries[0][0]  * entries[1][3] * entries[3][2] + 
             entries[1][0]  * entries[0][2] * entries[3][3] - 
             entries[1][0]  * entries[0][3] * entries[3][2] - 
             entries[3][0] * entries[0][2] * entries[1][3] + 
             entries[3][0] * entries[0][3] * entries[1][2];

   inv.entries[2][2] = entries[0][0]  * entries[1][1] * entries[3][3] - 
             entries[0][0]  * entries[1][3] * entries[3][1] - 
             entries[1][0]  * entries[0][1] * entries[3][3] + 
             entries[1][0]  * entries[0][3] * entries[3][1] + 
             entries[3][0] * entries[0][1] * entries[1][3] - 
             entries[3][0] * entries[0][3] * entries[1][1];

   inv.entries[3][2] = -entries[0][0]  * entries[1][1] * entries[3][2] + 
              entries[0][0]  * entries[1][2] * entries[3][1] + 
              entries[1][0]  * entries[0][1] * entries[3][2] - 
              entries[1][0]  * entries[0][2] * entries[3][1] - 
              entries[3][0] * entries[0][1] * entries[1][2] + 
              entries[3][0] * entries[0][2] * entries[1][1];

   inv.entries[0][3] = -entries[0][1] * entries[1][2] * entries[2][3] + 
             entries[0][1] * entries[1][3] * entries[2][2] + 
             entries[1][1] * entries[0][2] * entries[2][3] - 
             entries[1][1] * entries[0][3] * entries[2][2] - 
             entries[2][1] * entries[0][2] * entries[1][3] + 
             entries[2][1] * entries[0][3] * entries[1][2];

   inv.entries[1][3] = entries[0][0] * entries[1][2] * entries[2][3] - 
            entries[0][0] * entries[1][3] * entries[2][2] - 
            entries[1][0] * entries[0][2] * entries[2][3] + 
            entries[1][0] * entries[0][3] * entries[2][2] + 
            entries[2][0] * entries[0][2] * entries[1][3] - 
            entries[2][0] * entries[0][3] * entries[1][2];

   inv.entries[2][3] = -entries[0][0] * entries[1][1] * entries[2][3] + 
              entries[0][0] * entries[1][3] * entries[2][1] + 
              entries[1][0] * entries[0][1] * entries[2][3] - 
              entries[1][0] * entries[0][3] * entries[2][1] - 
              entries[2][0] * entries[0][1] * entries[1][3] + 
              entries[2][0] * entries[0][3] * entries[1][1];

   inv.entries[3][3] = entries[0][0] * entries[1][1] * entries[2][2] - 
             entries[0][0] * entries[1][2] * entries[2][1] - 
             entries[1][0] * entries[0][1] * entries[2][2] + 
             entries[1][0] * entries[0][2] * entries[2][1] + 
             entries[2][0] * entries[0][1] * entries[1][2] - 
             entries[2][0] * entries[0][2] * entries[1][1];

   return inv;
}

// Reduce mod3 entrywise
// Resulting entries are non-negative
Matrix Matrix::mod3(void) {
   Matrix M(rows, cols);
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Reducing matrix mod3" << endl;
   }

   for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
         M.entries[i][j] = ((entries[i][j]%3) + 3)%3;
      }
   }
   return M;
}

// Print to file
// Output format: full rows of space separated entries; rows separated by newlines.
void Matrix::print(ofstream &out_ptr) {
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Printing matrix to file" << endl;
   }

   for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
         out_ptr << entries[i][j] << " ";
      }
      out_ptr << endl;
   }
}
// Print to stdout 
// Output format: full rows of space separated entries; rows separated by newlines.
void Matrix::print() {
   if(VERBOSE==1) {
      cout << "[DEBUG:Matrix] Printing matrix to file" << endl;
   }

   for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
         cout << entries[i][j] << " ";
      }
      cout << endl;
   }
}



//*************************** OLD ********************************
//
vector<vector<int> > transpose(vector<vector<int> > matrix);
vector<vector<int> > matrix_mult(vector<vector<int> >, vector<vector<int> >);
int matrix_equal(vector<vector<int> >, vector<vector<int> >);
vector<vector<int> > mod3(vector<vector<int> >);
void print_matrix(vector<vector<int> >, int);

vector<vector<int> > transpose(vector<vector<int> > matrix) {
    vector<vector<int> > T = matrix;
        for(int i=0; i<matrix.size(); i++) {
                for(int j=0; j<matrix.size(); j++) {
            T[i][j] = matrix[j][i];
        }
    }
    return T;
}
// Assuming square matrix
vector<vector<int> > matrix_mult(vector<vector<int> > A, vector<vector<int> > B) {
    vector<vector<int> > C = A; // Fast init hacks much gud practise o yeaaaa
    for(int i=0; i<A.size(); i++) {
        for(int j=0; j<A.size(); j++) {
            int entry=0;
            for(int k=0; k<A.size(); k++) {
                //cout << "[DEBUG] Mult (" << i << "," << j 
                    //<< ") : " << A[i][k] << " with " << B[k][j] << endl;
                entry += (A[i][k] * B[k][j]);
            }
            C[i][j] = entry;
        }
    }
    return C;
}

int matrix_equal(vector<vector<int> > A, vector<vector<int> > B) {
    int flag=0;
    for(int i=0; i<A.size(); i++) {
        for(int j=0; j<A.size(); j++) {
            if(A[i][j] != B[i][j])
                flag = 1;
        }
    }
    return !flag;
}
// source: https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
vector<vector<int> > matrix_4x4Inverse(vector<vector<int> > M)
{
}

vector<vector<int> > mod3(vector<vector<int> > A) {
    vector<vector<int> > M = A;
    for(int i=0; i<A.size(); i++) {
        for(int j=0; j<A.size(); j++) {
            M[i][j] = abs(A[i][j])%3;
        }
    }
    return M;
}

void print_matrix(vector<vector<int> > A, int n) {
   for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
         cout << A[i][j] << " ";
      }
      cout << endl;
   }
}
