#ifndef _BITS
#define _BITS
#include <bits/stdc++.h>
#endif

using namespace std;

// Counts the number of triangles in a graph.
int triangle_cnt(vector<vector<int>> adj_lists);

// Computes adjacency list from a very specific input format
// WARNING: this is super specific.
// The format can be found in adj_lists, there are 720*12 points
vector<vector<int>> recover_adj_lists(string filename);
