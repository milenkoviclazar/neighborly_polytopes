#include <iostream>
#include <vector>

#include "eigen/Eigen/LU"

using namespace std;
using namespace Eigen;

vector<vector<int>> polytope;
vector<int> a;
Matrix<double, Dynamic, Dynamic> mat;
int r, c;
int n;

void brute(int lvl) {
    if (lvl == n) {
        for (int v = 0; v < polytope.size(); v++) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    mat(i, j) =
                            polytope[v][j] < r ? bool(i == polytope[v][j]) : bool(a[polytope[v][j] - r] & (1 << i));
                }
            }
            if ((int(mat.determinant()) & 1) == 0) {
                return;
            }
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << int(j < r ? bool(i == j) : bool(a[j - r] & (1 << i)));
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    for (a[lvl] = 1; a[lvl] < 1 << r; a[lvl]++) {
        bool linearlyDependent = false;
        for (int j = 0; j < lvl; j++) {
            if (a[j] == a[lvl]) {
                linearlyDependent = true;
                break;
            }
        }
        if (linearlyDependent) {
            continue;
        }
        brute(lvl + 1);
    }
}

void startSearch(const vector<vector<int>> &polytopeDescription, int rows, int cols) {
    mat.resize(rows, rows);
    polytope = polytopeDescription;
    a.clear();
    r = rows;
    c = cols;
    n = c - r;
    for (int i = 0; i < n; i++) {
        a.push_back(0);
    }
    brute(0);
}
