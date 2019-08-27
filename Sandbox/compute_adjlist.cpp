// This file is to create the adjacency lists L_{p,q} for a subgroup of the current group
//
// (18/08/2019)
// The current subgroup is elements that are Id mod 3
//
// Format of output file:
// [NUMBER OF LINES]
//
// [PAIR NUMBER] [COSET REP g_i] [COSET REP g_j]

#define COSET_FILE "../Data/coset_reps.txt"
#define FILENAME "../Data/HypMan.txt"
#define OUTFILE "../Data/190821Mod3adjlist.txt"

using namespace std;
#include <bits/stdc++.h>
#include "matrix_ops.h"

ifstream read_ptr;
ofstream write_ptr;
vector<vector<int> > mod3(vector<vector<int> > matrix);

int main(void) {
    vector<vector<int> > Id = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    int N = 4; // Size of matrices
    //cout << "[DEBUG]" << endl;

    // coset_reps: the final complete list of coset representatives
    vector<vector<vector<int> > > coset_reps;


    // thing: the thing that holds info about the edge labels and elements
    // it is a vector of pairs: < [vertex 1, vertex 2], list of matrices >
    vector<pair<pair<int,int>, vector<vector<vector<int> > > > > thing;

    // n: number of edge labels
    int n;

    cout << "[DEBUG] Reading cosets..." << flush;
    
    vector<vector<int> > M = Id;
    // READING COSET REPS
    read_ptr.open(COSET_FILE, ifstream::in);
    read_ptr >> n;
    //coset_reps.push_back(Id); // Id is always a coset representative
    for(int iii=0; iii<n; iii++) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                read_ptr >> M[i][j];
            }
        }
        coset_reps.push_back(M);
    }
    read_ptr.close();
    cout << " done" << endl;
    cout << "[DEBUG] Reading edge labels..." << flush;

    // READING MATRICES OF GAMMA (w/o redundancy mod 3 as we don't care otherwise)
    read_ptr.open(FILENAME, ifstream::in);
    read_ptr >> n;
    //cout << "[DEBUG] n is " << n << endl;
    for(int iii=0; iii<n; iii++) {
        // e1: first edge label
        // e2: second edge label
        // K: number of matrices to parse
        int e1, e2, K;
        read_ptr >> e1;
        read_ptr >> e2;
        read_ptr >> K;
        //cout << "[DEBUG] Edge label: " << e1 << " " << e2 << endl;

        // matrices: list of matrices witnessing closeness
        vector<vector<vector<int> > > matrices;

        // label: the edge label
        pair<int,int> label = make_pair(e1,e2);

        for(int jjj=0; jjj<K; jjj++) {
            vector<vector<int> > M = Id;
            // Parse matrix
            for(int i=0; i<N; i++) {
                for(int j=0; j<N; j++) {
                    read_ptr >> M[i][j];
                }
            }

            // Check MOD3 if matrix is not in list already
            for(int i=0; i<matrices.size(); i++) {
                if(matrix_equal(mod3(M), mod3(matrices[i]))) {
                    cout << "[DEBUG] Matrix already in list..." << endl;
                    goto _jjj; // jjj loop
                }
            } // i

            matrices.push_back(M);
_jjj:; // Continue label for jjj loop
        } // jjj

        // Done reading, add whole thing to thing
        thing.push_back(make_pair(label, matrices));
    } // iii
    cout << " done" << endl;
    
    // edge_list: the list of edges between points of the cover
    //            Format: [original point] [coset representative]
    vector<vector<int> > edge_list(thing.size(), vector<int>(coset_reps.size()));

    cout << "[DEBUG] Coset representatives: " << coset_reps.size() << endl;

    // -------------------- Reading complete ------------------------
    cout << "[DEBUG] ------------- Creating lists --------------" << endl;
    write_ptr.open(OUTFILE, ofstream::out);

    // e_cnt: number of edges
    int e_cnt=0;
    for(int iii=0; iii<thing.size(); iii++) { // loop over pairs (p,q)
        cout << "[DEBUG] Pair " << iii << ", size of list: " << thing[iii].second.size() << endl;
        for(int i=0; i<coset_reps.size(); i++) {
            for(int j=i; j<coset_reps.size(); j++) { // loop over pairs (g_i,g_j), j>=i
                // l_cnt: variable checking how many elements witness closeness
                int l_cnt=0;
                for(int k=0; k<thing[iii].second.size(); k++) { // loop over all elts in L(p,q)
                    // Check if g_j l is g_i mod 3
                    vector<vector<int> > T = matrix_mult(coset_reps[j], thing[iii].second[k]);
                    if(matrix_equal(mod3(T), mod3(coset_reps[i]))) {
                        if(l_cnt>0) {
                            cout << "[DEBUG] !!!!!!!!!!! Problem?" << endl;
                        }
                        // "put" an edge between g_i p, g_j q
                        cout << "[DEBUG] Edge between " << i << " and " << j 
                             << ". Witness: " << k << endl;
                        if(l_cnt==0) {
                            write_ptr << iii << " " << i << " " << j << endl;
                        }
                        l_cnt++;
                        
                    }
                }
                if(l_cnt>0) {
                    e_cnt++;
                }
            }
        }

    }

    cout << e_cnt << endl;


    return 0;
}

vector<vector<int> > mod3(vector<vector<int> > A) {
    vector<vector<int> > M = A;
    for(int i=0; i<A.size(); i++) {
        for(int j=0; j<A.size(); j++) {
            M[i][j] = A[i][j]%3;
        }
    }
    return M;
}
