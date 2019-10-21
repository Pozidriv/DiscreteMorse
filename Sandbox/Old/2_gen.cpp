// This file is to attempt generating all coset representatives from only two elements
// According to Mike this should be the case for most pairs.
//
// (01/09/2019)
//
// (05/09/2019)
// So apparently the result I got is very unsettling. 
// I will try with other elements.

using namespace std;
#include <bits/stdc++.h>
#include "matrix_ops.h"

// generate_elts: Recursive function to generate all elts of distance r of origin in the free gp.
//                Returns the list of words. Convention: Capital letter = inverse
vector<vector<char> > generate_elts(int r, int current=0);
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

   write_ptr.open("../Data/coset_reps.txt", ofstream::out);

   // radius: longest distance of a word from the origin
   int radius=10; 

   // A,B: the two generating matrices

   vector<vector<vector<int> > > coset_reps;
   vector<pair<vector<vector<int> >,char> > temp;

   vector<vector<int> > xirtam=A;
   int orderA=0,orderB=0;
   while(!matrix_equal(mod3(xirtam), Id)) {
      print_matrix(xirtam, 4);
      cout << endl;
      xirtam = mod3(matrix_mult(A, xirtam));
      orderA++;
      if(orderA >= 1000) {
         cout << "[DEBUG] problem..." << endl;
      }
   }
   cout << "[DEBUG] A has order " << orderA << endl;
   cin >> orderA;
   
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
           for(int k=0; k<coset_reps.size(); k++) {
               vector<vector<int> > T;
               if(matrix_equal(mod3(matrix), mod3(coset_reps[k]))) {
                   //cout << "[DEBUG] Matrix already in list" << endl;
                   redund++;
                   goto _continueloop;
               }
               T = matrix_mult(mod3(matrix_4x4Inverse(mod3(coset_reps[k]))), mod3(matrix));

               if(matrix_equal(mod3(T), Id)) {
                   cos++;
                   if(flag) {
                       cout << "[DEBUG] Coset representative already in list" << endl;
                   }
                   goto _continueloop;
               }
           }

           cout << "[DEBUG] New element " << coset_reps.size() << endl;
           coset_reps.push_back(matrix);
   _continueloop:;
       flag=0;
       }
   }
   /*
   for(int i=0; i<words.size(); i++) {
       cout << "[DEBUG] ";
       for(int j=0;j<words[i].size();j++) {
           cout << words[i][j];
       }
       cout << endl;
   }
   */




   for(int iii=0; iii<coset_reps.size(); iii++) {
       //cout << iii << endl;
       for(int jjj=0; jjj<coset_reps[iii].size(); jjj++) {
           for(int kkk=0; kkk<coset_reps[iii][jjj].size(); kkk++) {
               write_ptr << coset_reps[iii][jjj][kkk] << " ";
           }
           write_ptr << endl;
       }
       write_ptr << endl;
   }
   write_ptr << coset_reps.size();

   cout << "[DEBUG] Redundant matrices: " << redund << endl;
   cout << "[DEBUG] Redundant representatives: " << cos << endl;

   return 0;
}

// Obsolete?
vector<vector<char> > generate_elts(int r, int current) {
   vector<vector<char> > ret, temp;
   if(current == r) { 
       ret.push_back({'a'});
       ret.push_back({'A'});
       ret.push_back({'b'});
       ret.push_back({'B'});
   } else {
       temp = generate_elts(r, ++current);
       for(int i=0; i<temp.size(); i++){
           vector<char> word = temp[i];
           word.push_back('a');
           ret.push_back(word);
           word.pop_back();
           word.push_back('A');
           ret.push_back(word);
           word.pop_back();
           word.push_back('b');
           ret.push_back(word);
           word.pop_back();
           word.push_back('B');
           ret.push_back(word);
           word.pop_back();
       }
   }
   return ret;
}

// NOTATION : a = matrix A, A = inverse of matrix A
// The returned thing is a vector of < MATRIX, last matrix multiplied by >
vector<pair<vector<vector<int> >, char > > generate_matrices(int r, int current) {
   vector<pair<vector<vector<int> >, char > > ret, temp;
   if(current == r) { 
       ret.push_back(make_pair(A, 'a'));
       ret.push_back(make_pair(matrix_4x4Inverse(A), 'A'));
       ret.push_back(make_pair(B, 'b'));
       ret.push_back(make_pair(matrix_4x4Inverse(B), 'B'));
   } else {
   vector<pair<vector<vector<int> >,char> > temp = generate_matrices(r, ++current);
       for(int i=0; i<temp.size(); i++){
           
           vector<vector<int> > matrix = temp[i].first;
           char prev = temp[i].second;

      // Use mod3 here if you don't care about keeping track of the original matrices
      // It will be faster (hopefully)
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
