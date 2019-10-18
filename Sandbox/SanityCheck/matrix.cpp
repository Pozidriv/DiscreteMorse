#include <experimental/filesystem> // Link with -lstdc++fs !!
#include <bits/stdc++.h>
#include "../matrix_ops.h"
using namespace std;
namespace fs = std::experimental::filesystem;

bool test_op(string filename, string correct, string operation);

// Testing matrix_ops on some things
int main(void) {
   cout << "Testing matrix file..." << endl;
   
   string work_directory = "./tests/matrix/";
   stringstream sub_directory;
   sub_directory << work_directory;
   
   vector<string> operations = { "add", "sub", "mult", "4x4inverse", "transpose", "mod3" };
   
   for(int i=0; i<operations.size(); i++) {
      sub_directory << operations[i];
      for(auto& p: fs::directory_iterator(sub_directory.str())) {
         sub_directory << "/valid/" << p.file_name;
         test_op(p.path(), sub_directory, i);
      }

      sub_directory.clear();
      sub_directory << work_directory;
   }

   return 0;
}

// This function will read the matrices from the specified file and execute the specified operation.
// Then compares output with the correct file
// Expecting matrices of size 4x4
bool test_op(string filename, string correct, int operation) {
   ifstream operands_ptr, correct_ptr;
   vector<Matrix> matrices;
   Matrix result, expected;
   int n;

   operands_ptr.open(filename, ifstream::in);
   correct_ptr.open(correct, ifstream::in);
   operands_ptr >> n;

   for(int i=0; i<n; i++) {
      matrices.push_back(Matrix(operands_ptr, 4));
   }

   // Perform operation
   switch(operation) {
      case 0 : result = matrices[0]+matrices[1]; // Add
                   break;
      case 1 : result = matrices[0]-matrices[1]; // Sub
                   break;
      case 2 : result = matrices[0]*matrices[1]; // Mult
                   break;
      case 3 : result = matrices[0].inverse(); // Inverse
                   break;
      case 4 : result = matrices[0].transpose(); //Transpose
                   break;
      case 5 : result = matrices[0].mod3(); // Mod3
                   break;
   }

   // Compare versus correct value
   expected = Matrix(correct_ptr, 4);

   operands_ptr.close();
   correct_ptr.close();
   return (result == expected);
}
