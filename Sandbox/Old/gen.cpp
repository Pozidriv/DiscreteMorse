// This file is to attempt generating all elements of SO(Q)(L/3L)
// (05/09/2019) 
//
// 

using namespace std;
#include <bits/stdc++.h>
#include "matrix_ops.h"

// generate_elts: Recursive function to generate all elts of distance r of origin in the free gp.
//                Returns the list of words. Convention: Capital letter = inverse
vector<pair<vector<vector<int> >, char> > generate_matrices(int r, int current=0);

//vector<vector<int> > A = {{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,0,-1}};//1,1
vector<vector<int> > A = {{-3,-2,4,2},{-4,-2,3,2},{2,0,-2,-1},{-14,-7,14,8}}; //12,10
vector<vector<int> > B = {{2,0,-2,-1},{0,1,0,0},{5,0,-2,-2},{-14,0,7,6}}; //4,5
vector<vector<int> > InvA, InvB;

ofstream write_ptr;

int main(void) {
    // For debug printing purposes
    int flag=0, inc=1000, flag_cnt=1000, redund=0, cos=0;

    vector<vector<int> > Id = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    InvA = matrix_4x4Inverse(A);
    InvB = matrix_4x4Inverse(B); 
    A = mod3(A);
    B = mod3(B);
    InvB = mod3(InvB);
    InvA = mod3(InvA);

    write_ptr.open("../Data/elements.txt", ofstream::out);

    // radius: longest distance of a word from the origin
    int radius=10; 

    // A,B: the two generating matrices

    // elelements: the elements of SO(Q)(L/3L)
    vector<vector<vector<int> > > elements;
    vector<pair<vector<vector<int> >,char> > temp;
    
    for(int r=0; r<=radius; r++) {
        cout << r << endl;
        temp = generate_matrices(r);
        cout << "[DEBUG] Number of elements: " << temp.size() << endl;
        for(int i=0; i<temp.size(); i++) {
            vector<vector<int> > matrix;
            matrix = temp[i].first;

            if(i>flag_cnt) {
                flag = 1;
                flag_cnt += inc;
            }
            if(flag) {
                cout << "[DEBUG] " << i << endl;
            }

            for(int k=0; k<elements.size(); k++) {
                vector<vector<int> > T;
                if(matrix_equal(mod3(matrix), (elements[k]))) {
                    //cout << "[DEBUG] Matrix already in list" << endl;
                    redund++;
                    goto _continueloop;
                }
            }

            cout << "[DEBUG] New element " << elements.size() << endl;
            elements.push_back(mod3(matrix));
    _continueloop:;
        flag=0;
        }
    }



    for(int iii=0; iii<elements.size(); iii++) {
        //cout << iii << endl;
        for(int jjj=0; jjj<elements[iii].size(); jjj++) {
            for(int kkk=0; kkk<elements[iii][jjj].size(); kkk++) {
                write_ptr << elements[iii][jjj][kkk] << " ";
            }
            write_ptr << endl;
        }
        write_ptr << endl;
    }
    write_ptr << elements.size();

    cout << "[DEBUG] Redundant matrices: " << redund << endl;
    cout << "[DEBUG] Redundant representatives: " << cos << endl;

    return 0;
}


// NOTATION : a = matrix A, A = inverse of matrix A
// The returned thing is a vector of < MATRIX, last matrix multiplied by >
vector<pair<vector<vector<int> >, char > > generate_matrices(int r, int current) {
    vector<pair<vector<vector<int> >, char > > ret, temp;
    if(current == r) { 
        ret.push_back(make_pair(A, 'a'));
        ret.push_back(make_pair(InvA, 'A'));
        ret.push_back(make_pair(B, 'b'));
        ret.push_back(make_pair(InvB, 'B'));
    } else {
    vector<pair<vector<vector<int> >,char> > temp = generate_matrices(r, ++current);
        for(int i=0; i<temp.size(); i++){
            vector<vector<int> > matrix = temp[i].first;
            char prev = temp[i].second;

            if(prev != 'A') { // Multiplying by A
                matrix = mod3(matrix_mult(matrix, A));
                ret.push_back(make_pair(matrix, 'a'));
            }
            
            if(prev != 'a') { // Multiplying by a
                matrix = mod3(matrix_mult(matrix, InvA));
                ret.push_back(make_pair(matrix, 'A'));
            }
            
            if(prev != 'B') { // Multiplying by b
                matrix = mod3(matrix_mult(matrix, B));
                ret.push_back(make_pair(matrix, 'b'));
            }
            
            if(prev != 'b') { // Multiplying by a
                matrix = mod3(matrix_mult(matrix, InvB));
                ret.push_back(make_pair(matrix, 'B'));
            }
        }
    }
    return ret;
}
