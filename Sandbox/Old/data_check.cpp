// This file is to check the validity of the data sent by Aurel (05/08/2019)
// The data was found to be correct up to transposing the matrix (09/08/2019)
// The file is now made to parse the data and produce a readable file (09/08/2019)
// LAST UPDATE (18/08/2019)
//
// The format of the readable file is as follows:
// [N]
//
// [EDGE LABEL]
// [K]
// [LIST OF 4x4 MATRICES]
//
//
// N represents the number of edge labels followed by matrices
// K represents the number of matrices following the edge label
// Edge labels are two integers
//

#define FILENAME "../Data/DataMikeStudent2.txt"

#include<bits/stdc++.h>
#include "matrix_ops.h"
using namespace std;

ifstream read_ptr;
ofstream write_ptr;



int main(void) {
    // M will be the read group elements, A will be the matrix associated to our quadratic form.
    vector<vector<int> > M;
    vector<vector<int> > A = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,-7}};
    string buffer, token;
    int N = 4; // I hate c++11
    int dsfjkfsdjksdfksdf=0; // counter for something

    //cout << "Reading file..." << endl;
    read_ptr.open(FILENAME, ifstream::in);

    // Init M
    M = vector<vector<int> >(N, vector<int>(N, 0));

    // Debug
    /*
    for(int i=0; i<A.size(); i++) {
        for(int j=0; j<A.size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    */

    // no_matrices: number of matrices for current edge label
    int no_matrices=0;

    // matrices: the collection of matrices associated to the current edge
    vector<vector<vector<int> > > matrices;

    // Parse input
    // Input format is a bunch of things of the form [ EDGE LABEL ] [ MATRIX ] ... [ MATRIX ]
    while(getline(read_ptr, buffer)) {
        // pos: start position of new token
        // len: length of new token
        // buff_len: length of line being parsed
        // count: position in the matrix
        // elabel: keeps track of which edgelabel we've last seen
        int pos=0, len=0, buff_len=buffer.size(), count=0, elabel=0; 
        //cout << "[DEBUG] Current line: " << buffer << endl;

        // Discard '[', ']' lines
        if(buff_len <= 3) continue;

        // Tokenize buffer
        while(pos < buff_len) {
            //cout << "[DEBUG] pos: " << pos << endl;
            // Extract 1st token
            len = buffer.find(" ", pos);

            // In case no match was found
            if(len == string::npos) 
                len = buffer.size()-pos;
            else
                len = len - pos +1;
            len = (len <= 0) ? 1 : len;
            token = buffer.substr(pos, len-1);
            pos += len;

            // Remove comas at the end
            if(token[token.size()-1] == ',') {
                //cout << "[DEBUG] Removing comma" << endl;
                token = token.substr(0, token.size()-1);
            }
            //cout << "[DEBUG] Token: '" << token << "'" << endl;

            if(token[0] == '[' || token[0] == ']' || buffer.size() <9) {
                //cout << "[DEBUG] '[', ']' case. Token: " << token << endl;

                // If current line is not an edge label, ignore it
                if(buffer.size() >=9)
                    continue;
                
                // otherwise extract the edge label
                else {
                    if(token[0] == '[') {

                        if(elabel == 0) {
                            // PRINT MATRICES
                            // Print matrix number
                            cout << endl << no_matrices << endl << endl;
                            // WARNING: at this point we are printing matrices for the previous edge label
                            // Print matrices (this is not the most readable format but whatever
                            for(int k=0; k<matrices.size(); k++) {
                                for(int i=0; i<N; i++) {
                                    for(int j=0; j<N; j++) {
                                        cout << matrices[k][i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl;
                            }
                            cout << endl;
                            // Reset matrix counter
                            no_matrices = 0;
                            // Reset matrix vector
                            matrices.clear();
                            elabel++;
                        }


                        // Print edge label
                        token = token.substr(1);
                        cout << token << " ";
                        continue;
                    }

                }
            // Case where we have a matrix element
            } else {
                int i=count/N, j=count%N;
                //cout << "[DEBUG] i: " << i << ", j: " << j << endl;
                istringstream(token) >> M[i][j];
                count++;
            }

            //cout << "[DEBUG] Token: " << token << endl;
            if(count == 16) {
                // Finished reading matrix. Add it to our matrices vector
                matrices.push_back(M);

                // Increment matrix count
                no_matrices++;
                
                
                
                // Finished reading matrix. Perform check.

                /*************************** CHECK CODE *********************************/
                /*
                vector<vector<int> > T = transpose(M),S;
                    cout << "[DEBUG] Transpose:" << endl;
                    for(int i=0; i<T.size(); i++) {
                        for(int j=0; j<T.size(); j++) {
                            cout << T[i][j] << " ";
                        }
                        cout << endl;
                    }
                S = matrix_mult(M, A);
                
                    cout << "[DEBUG] Intermediate:" << endl;
                    for(int i=0; i<S.size(); i++) {
                        for(int j=0; j<S.size(); j++) {
                            cout << S[i][j] << " ";
                        }
                        cout << endl;
                    }
                T = matrix_mult(S, T);
                
                    cout << "[DEBUG] Result:" << endl;
                    for(int i=0; i<T.size(); i++) {
                        for(int j=0; j<T.size(); j++) {
                            cout << T[i][j] << " ";
                        }
                        cout << endl;
                    }
                
                if(!matrix_equal(T, A)) {
                    cout << "------------------We have a problem------------------" << endl;
                    cout << "[DEBUG] Matrix:" << endl;
                    for(int i=0; i<M.size(); i++) {
                        for(int j=0; j<M.size(); j++) {
                            cout << M[i][j] << " ";
                        }
                        cout << endl;
                    }
                    cout << "[DEBUG] Mult:" << endl;
                    for(int i=0; i<T.size(); i++) {
                        for(int j=0; j<T.size(); j++) {
                            cout << T[i][j] << " ";
                        }
                        cout << endl;
                    }
                }
                */
                /********************************* END OF CHECK CODE *************************/
            }

            // If edge label line and second token
            if(buffer.size() < 9) {
                if(elabel != 0) {
                    //cout << "[DEBUG] SECOND LABEL" << endl;
                    cout << token << endl;
                    dsfjkfsdjksdfksdf++; // increment counter for something
                    continue;
                }
            }
        }

    }
    
    // PRINT MATRICES
    // Print matrix number
    cout << endl << no_matrices << endl << endl;
    // WARNING: at this point we are printing matrices for the previous edge label
    // Print matrices (this is not the most readable format but whatever
    for(int k=0; k<matrices.size(); k++) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                cout << matrices[k][i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
    // Reset matrix counter
    no_matrices = 0;
    // Reset matrix vector
    matrices.clear();

    cout << dsfjkfsdjksdfksdf << endl; // print counter for something
    return 0;
}

