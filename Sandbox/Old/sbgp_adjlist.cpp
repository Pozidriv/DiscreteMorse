// This file is to create the coset representatives for a subgroup of the current group
//
// (18/08/2019)
// The current subgroup is elements that are Id mod 3
//
// (26/08/2019)
// Turns out what I did is wrong, I was computing an incomplete list of coset reps.
//

#define FILENAME "../Data/HypMan.txt"

using namespace std;
#include <bits/stdc++.h>
#include "matrix_ops.h"

ifstream read_ptr;

int main(void) {
    vector<vector<int> > Id = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    read_ptr.open(FILENAME, ifstream::in);

    int N = 4; // Size of matrices
    //cout << "[DEBUG]" << endl;

    // n: number of edge labels
    int n;
    read_ptr >> n;
    
    // coset_reps: the final complete list of coset representatives
    vector<vector<vector<int> > > coset_reps;
    coset_reps.push_back(Id); // Id is always a coset representative

    for(int iii=0; iii<n; iii++) {
        // e1: first edge label
        // e2: second edge label
        // K: number of matrices to parse
        int e1, e2, K;
        read_ptr >> e1;
        read_ptr >> e2;
        read_ptr >> K;
        //cout << "[DEBUG] Edge label: " << e1 << " " << e2 << endl;

        for(int jjj=0; jjj<K; jjj++) {
            vector<vector<int> > M = Id;
            // Parse matrix
            for(int i=0; i<N; i++) {
                for(int j=0; j<N; j++) {
                    read_ptr >> M[i][j];
                }
            }

            // Check MOD3 if matrix is not in list already
            for(int i=0; i<coset_reps.size(); i++) {
                if(matrix_equal(mod3(M), mod3(coset_reps[i]))) {
                    //cout << "[DEBUG] Matrix already in list..." << endl;
                    goto _jjj; // jjj loop
                }
            } // i

            // Check if there is a coset rep such that g^{-1}M is Id mod 3
            for(int i=0; i<coset_reps.size(); i++) {
                vector<vector<int> > T = matrix_mult(matrix_4x4Inverse(coset_reps[i]), M);

                // If so, continue jjj loop
                if(matrix_equal(mod3(T), Id)) {
                    cout << "[DEBUG] Coset representative already in list" << endl;
                    goto _jjj;
                }
                
            }

            coset_reps.push_back(M);
_jjj:; // Continue label for jjj loop
        } // jjj
    } // iii

    //cout << "Found " << coset_reps.size() << " coset representatives." << endl;
    cout << coset_reps.size() << endl;
    for(int i=0; i<coset_reps.size(); i++) {
        for(int j=0; j<N; j++) {
            for(int k=0; k<N; k++) {
                cout << coset_reps[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

