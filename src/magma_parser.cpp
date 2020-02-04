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
#ifndef _MAGMA_PARSER
#define _MAGMA_PARSER
#include "magma_parser.h"
#endif


// Reading 4x4 matrices presented with the following format:
// [ EDGE_LABEL ]
// [ { MATRIX } ]
// where we have the formats being
// EDGE_LABEL: "int, int"
// MATRIX: [ 16x" int, " ]

void magma_parser_matrix(ifstream& in, vector<vector<Matrix>>& ret) {
   string buffer;
   getline(in, buffer); // Discard useless "[" line
   debug("magma_parser_matrix", "\""+buffer+"\"");

   while(getline(in, buffer)) {
      debug("magma_parser_matrix", "\""+buffer+"\"");
      if(buffer.size() < 3) {
         debug("magma_parser_matrix", "Line size below 3. Breaking.");
         break;
      }
      buffer = buffer.substr(1, buffer.size()-3); // Discard the "[", "],"
      //debug("magma_parser_matrix", "\""+buffer+"\"");
      int pos=0;
      while(pos = buffer.find(",")) { // Discard ","
         if(pos==-1) break;
         buffer.replace(pos, 1, " ");
      }
      //debug("magma_parser_matrix", "\""+buffer+"\"");
      stringstream ss(buffer);
      Matrix ting(4);
      
      int a=0;
      for(int i=0; i<16; i++) {
         string tmp;
         ss >> a;
         //a = stoi(tmp);
         //debug("magma_parser_matrix", "a:", a);
         ting.entries[i/4][i%4] = a;
      }
      ret[ret.size()-1].push_back(ting);
   }
   getline(in, buffer); // Discard useless "]" line
}

void readable_write(ofstream& out, vector<vector<Matrix>>& ret, vector<vector<int>>& elabel) {
   out << ret.size() << endl;
   out << endl;
   for(int i=0; i<ret.size(); i++) {
      out << elabel[i][0] << " " << elabel[i][1] << endl;
      out << ret[i].size() << endl;
      for(int j=0; j<ret[i].size(); j++) {
         ret[i][j].print(out);
      }
      out << endl;
   }
}

void magma_4x4read(ifstream& in, vector<vector<Matrix>>& ret, vector<vector<int>>& elabel) {
   debug("magma_4x4read", "Reading line");
   string buffer;
   while(getline(in, buffer)) {
      debug("magma_4x4read", "Line: ", "\""+buffer+"\"");
      if(buffer.size() > 0 && buffer.substr(0,1) == "[") {
         int a, b, comma_pos, bracket_pos;
         comma_pos = buffer.find(",");
         debug("magma_4x4read", "comma_pos: ", comma_pos);
         //debug("magma_4x4read", buffer.substr(1, comma_pos-2));
         a = stoi(buffer.substr(1, comma_pos-1));
         bracket_pos = buffer.find("]");
         debug("magma_4x4read", "bracket_pos: ", bracket_pos);
         b = stoi(buffer.substr(comma_pos+1, bracket_pos-comma_pos));
         
         debug("magma_4x4read", "a", a, "| b", b);
         elabel.push_back(vector<int>({a,b}));
         debug("magma_4x4read", "elabel: ", elabel.size());
         ret.push_back(vector<Matrix>());
         magma_parser_matrix(in, ret);
      }
   }
}


void magma_parser_elabel(ifstream& in, vector<vector<Matrix>>& ret, vector<vector<int>>& elabel) {
}

