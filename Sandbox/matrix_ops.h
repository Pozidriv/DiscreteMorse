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

      void init_matrix(matrix);

      Matrix transpose(void); // Compute matrix tranpose
      Matrix inverse(void);   // Compute 4x4 matrix inverse (of an invertible matrix)
      Matrix mult(Matrix);    // Multiply two matrices
      bool equal(Matrix);     // Check entrywise equality
      Matrix mod3(void);      // Reduce mod3 entrywise

      void print(ofstream);   // Print to file

      // CONSTRUCTORS
      
      Matrix();                // Default constructor
      Matrix(int);             // Creates empty matrix of specified size
      Matrix(ifstream, int);   // Construct from file input

      // OPERATOR OVERLOADING

      Matrix operator+ (const Matrix&);
      Matrix operator- (const Matrix&);
      Matrix operator* (const Matrix&);
};

// Standard constructor
Matrix::Matrix() {
}

// Empty square matrix constructor
Matrix::Matrix(int n) {
    rows = n; cols = n;
    entries = vector<vector<int> >(n, vector<int>(n));
}

// File input constructor
// Expected input: 
// - square matrix of dimension n
// - space/newline separated string of integers
// - full 1st row, then full 2nd row, etc...
Matrix::Matrix(ifstream str, int n) {
    if(VERBOSE==1) {
        cout << "[DEBUG] Constructing matrix from file..." << endl;
    }

    rows = n; cols = n;
    entries = vector<vector<int> >(n, vector<int>(n));
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            ifstream >> entries[i][j];
        }
    }
}

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
    int inv[16], m[16];
    vector<vector<int> > ret = M;

    for (int i = 0; i < 16; i++) {
        m[i] = M[i/4][i%4];
    }

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    for (int i = 0; i < 16; i++) {
        ret[i/4][i%4] = inv[i];
    }

    return ret;
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
