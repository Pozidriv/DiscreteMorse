#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif
#ifndef _UTIL_IO
#define _UTIL_IO
#include "util_io.h"
#endif
#ifndef _MATRIX
#define _MATRIX
#include "matrix.h"
#endif

// Reading 4x4 matrices presented with the following format:
// [ EDGE_LABEL ]
// [ { MATRIX } ]
// where we have the formats being
// EDGE_LABEL: "int, int"
// MATRIX: [ 16x" int, " ]

void readable_write(ofstream& out, vector<vector<Matrix>>& ret, vector<int[2]>& elabel) {
}

void magma_4x4read(ifstream& in, vector<vector<Matrix>>& ret, vector<int[2]>& elabel) {
   string buffer;
   while(getline(in, buffer)) {
      if(buffer[0] == "[") {
         int a,b,comma_pos, bracket_pos;
         comma_pos = buffer.find(",");
         a = stoi(buffer.substr(2, comma_pos-2);
         bracket_pos = buffer.find("]");
         b = stoi(buffer.substr(comma_pos+1, bracket_pos-comma_pos);
         
         debug("magma_4x4read", "a", a, "| b", b);
         elabel.push_back({ a, b });
         ret.push_back(vector<vector<Matrix>>());
         magma_parser_matrix(in, ret);
      }
   }
}

void magma_parser_matrix(ifstream& in, vector<vector<Matrix>>& ret) {
   getline(in, buffer); // Discard useless "[" line

   while(getline(in, buffer)) {
      if(buffer.size() < 3) {
         break;
      }
      buffer = buffer.substr(1, buffer.size()-2); // Discard the "[", "]"
      int pos=0;
      while(pos = buffer.find(",")) { // Discard ","
         buffer.replace(pos, 1, " ");
      }
      stringstream ss(buffer);
      Matrix ting(4);
      
      int a=0;
      for(int i=0; i<16; i++) {
         a << ss;
         debug("magma_parser_matrix", "a:", a);
         ting[i/4][i%4] = a;
      }
      ret[ret.size()-1].push_back(ting);
   }
   getline(in, buffer); // Discard useless "]" line
}

void magma_parser_elabel(ifstream& in, vector<vector<Matrix>>& ret, vector<int[2]>& elabel) {
}

