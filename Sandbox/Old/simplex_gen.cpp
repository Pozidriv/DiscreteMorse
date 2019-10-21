#include <bits/stdc++.h>
using namespace std;

ifstream read_ptr;
ofstream write_ptr;

int main(void) {
    string file;
    cout << "Output file? "<< endl;
    cin >> file;

    write_ptr.open(file.c_str(), ofstream::out);

    int n;
    cout << "Dimension of simplex?" << endl;
    cin >> n;

    write_ptr << n << endl << n << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            write_ptr << ((i==j) ? 1 : 0) << " ";
        }
    }
    for(int i=0; i<n; i++) 
        write_ptr << 1 << " ";
    write_ptr << endl;
    return 0;
}
