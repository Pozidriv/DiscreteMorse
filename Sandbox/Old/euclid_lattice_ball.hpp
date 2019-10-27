// Generates a bunch of points along a euclidean lattice, all within some subspace of Rn
// Reads input from a file

// WARNING!!! Number of points goes up exponentially with the dimension.
// Adjust radius accordingly
#define RADIUS 2
#define HEADER "1 0.5 1"
#define POINT_TRAILER " 0"

#include <bits/stdc++.h>
using namespace std;

int is_linindep(vector<vector<int> >, int n); // Takes an nxn matrix and checks if it is of rank n.
int recurse(vector<vector<int> >* lattice, int n, vector<int> start, int index);
long int dot_prod(vector<vector<int> >* lattice, vector<int> point, int n);
ifstream read_ptr;
ofstream write_ptr;

int main(void) {
    // Fetching lattice info
    string file;
    cout << "GENERATING IN A BALL"<< endl;
    cout << "Input Filename !!! PLEASE MAKE SURE VECTORS ARE LIN INDEP !!!" << endl;
    cin >> file;
    read_ptr.open(file.c_str(), ifstream::in);
    cout << "Output Filename" << endl;
    cin >> file;
    write_ptr.open(file.c_str(), ofstream::out);

    int n; // Dimension of Euclidean space 
    read_ptr >> n;

    vector<vector<int> > lattice (n, vector<int>(n, 0));
    for(int i=0; i<n; i++) { // ith basis vector
        for(int j=0; j<n; j++) { // jth coordinate
            read_ptr >> lattice[i][j];
        }
    }
    /*
    if(!is_linindep(lattice, n)) {
        cout << "This is not a lattice." << endl;
        return 0;
    }
    */


    // WRITING TO FILE
    write_ptr << n << endl; // Dimension
    write_ptr << HEADER << endl; // k, s N
    cout << "[DEBUG] Recursing" << endl;
    recurse(&lattice, n, vector<int>(n,0), 0);


    read_ptr.close();
    write_ptr.close();

    return 0;
}

void print_pt(vector<int> pt) {
    for(int i=0; i<pt.size(); i++) {
        cout << pt[i] << " ";
    }
    return;
}

int recurse(vector<vector<int> >* lattice, int n, vector<int> start, int index) {
    long int dist = dot_prod(lattice, start, n);
    cout << "[DEBUG] current point: ";
    print_pt(start);
    cout << endl;
    cout << "[DEBUG] dist: " << dist << endl;
    cout << "[DEBUG] RADIUS*RADIUS: " << (long int)RADIUS*RADIUS << endl;
    if (dist > (long int) RADIUS*RADIUS) return 0; // If start vector is already out of range, return.

    if (index == n) { // Reached the bottom of the loop, print point and return
        cout << "[DEBUG] Printing point to file" << endl;
        for(int i=0; i<n; i++) write_ptr << " " << start[i];
        write_ptr << POINT_TRAILER << endl;
    } else { // Recurse  (not optimal but w/e)
        while(recurse(lattice, n, start, index+1)) { // Positive
            start[index]++;
        }
        start[index] = -1;
        while(recurse(lattice, n, start, index+1)) { // Negative
            start[index]--;
        }
    }

    // Two recursions: one positive, one negative.
    // If recursion at a certain point was too much, terminate
    
    return 1;
}

long int dot_prod(vector<vector<int> >* lattice, vector<int> point, int n) {
    long int value = 0;
    for(int i=0; i<n; i++) {
        long int temp = 0;
        for(int j=0; j<n; j++) {
           temp += (*lattice)[i][j] * point[i]; 
        }
        value += abs(temp*temp);
    }
    return value;
}

/*
// Essentially performs Gaussian elimination from Wikipedia
int is_linindep(vector<vector<int> > matrix, int n) {
    int h = 1, k = 1;
    while (h < n && k < n) {
        int i_max = (abs(matrix[h][k]) > abs(matrix[n-1][k])) ? h : n-1;
        if(matrix[i_max,k] = 0) k++;
        else { // swap rows h and i_max
            vector<int> temp = matrix[h];
            matrix[h] = matrix[i_max];
            matrix[i_max] = temp;
            for(int i=h+1; i<n; i++) {
                
            }
        }
}
*/
