#include <iostream>
#include <vector>

#include "eigen/Eigen/LU"

using namespace std;
using namespace Eigen;

bool get(vector<int> &a, vector<int> &swaps, int i, int j, int r) {
    int idx = 0;
    while (idx < r && swaps[idx] < j) {
        idx++;
    }
    if (idx < r && swaps[idx] == j) {
        return i == idx;
    }
    return a[i] & (1 << (j - idx));
}

void brute(vector<vector<int>> &polytope, vector<int> &a, int lvl, int r, int c) {
    if (lvl == r) {
        Matrix<double, Dynamic, Dynamic> A;
        A.resize(r, r);
        bool valid = true;
        for (int v = 0; v < polytope.size(); v++) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    A(i, j) = polytope[v][j] < r ? bool(i == polytope[v][j]) : bool(a[i] & (1 << (polytope[v][j] - r)));
                }
            }
            if ((int(A.determinant()) & 1) == 0) {
                valid = false;
                break;
            }
        }
        if (valid) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    cout << get(a, polytope[0], i, j, r);
                }
                cout << endl;
            }
            cout << endl;
        }
        return;
    }
    int n = c - r;
    for (a[lvl] = 0; a[lvl] < 1 << n; a[lvl]++) {
        brute(polytope, a, lvl + 1, r, c);
    }
}

