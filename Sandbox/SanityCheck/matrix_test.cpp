#include <experimental/filesystem> // Link with -lstdc++fs !! AFTER the filename
#include <bits/stdc++.h>
#include "../matrix.h"
using namespace std;
namespace fs = std::experimental::filesystem;

bool test_op(string filename, string correct, int operation);
string extract_filename(string path);

// Testing matrix_ops on some things
int main(void) {
   cout << "Testing matrix file..." << endl;
   
   string work_directory = fs::current_path();
   //string work_directory = "~/Documents/McGill/Masters/Thesis/DiscreteMorse/Algorithms/Code/Sandbox/SanityCheck/tests/matrix";
   stringstream sub_directory;
   sub_directory << work_directory << "/SanityCheck/tests/";
   cout << "[DEBUG] Work directory is " << work_directory << endl;
   
   vector<string> operations = { "add", "sub", "mult", "4x4inverse", "transpose", "mod3" };
   
   for(int i=0; i<operations.size(); i++) {
      cout << "Currently testing: \"" << operations[i] << "\"" << endl;
      sub_directory << operations[i];

      if(!fs::exists(sub_directory.str())) {
         cout << "Error: directory '" << sub_directory.str() << "' does not exist. Skipping" << endl;
         continue;
      }

      for(auto& p: fs::directory_iterator(sub_directory.str())) {
         
         if(!is_directory(p)) {
            stringstream valid;
            valid << sub_directory.str() << "/valid/" << extract_filename(p.path());
            string tmp;
            tmp = valid.str();
            //cout << "[DEBUG] Correct is " << tmp << endl;

            // Perform test
            cout << extract_filename(p.path()) << " ... " << flush;
            if(test_op(p.path(), tmp, i) == false) {
               cout << "FAILED" << endl;
            } else {
               cout << "PASSED" << endl;
            }
         }
      }

      sub_directory.str("");
      sub_directory << work_directory << "/SanityCheck/tests/";
   }

   return 0;
}

// Helper function to extract only the filename of a full path string
string extract_filename(string path) {
   reverse_iterator<string::iterator> rev(path.end());
   stringstream tmp;
   while(*rev != '/') {
      tmp << *rev++;
   }
   string convert;
   tmp >> convert;
   string result(convert.rbegin(), convert.rend()); // Create the reverse of the stringstream
   return result;
}

// This function will read the matrices from the specified file and execute the specified operation.
// Then compares output with the correct file
// Expecting matrices of size 4x4
bool test_op(string filename, string correct, int operation) {
   /*
   cout << endl 
      << "[DEBUG:test_op] \nfilename: '" << filename 
      << "'\ncorrect: '" << correct 
      << "'\nop: " << operation << endl;
   */
   ifstream operands_ptr, correct_ptr;
   vector<Matrix> matrices;
   Matrix result, expected;
   int n;

   operands_ptr.open(filename, ifstream::in);
   operands_ptr >> n;

   for(int i=0; i<n; i++) {
      Matrix A(operands_ptr, 4);
      matrices.push_back(A);
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

   operands_ptr.close();
   // Compare versus correct value
   correct_ptr.open(correct, ifstream::in);
   expected = Matrix(correct_ptr, 4);

   if(!(result == expected)) {
      cout << endl << "EXPECTED" << endl;
      expected.print();
      cout << "RESULT" << endl;
      result.print();
   }
   correct_ptr.close();
   return (result == expected);
}
