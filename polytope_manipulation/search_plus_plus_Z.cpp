#include <iostream>
#include <vector>
#include "eigen/Eigen/LU"
#include "io_utils.h"

using namespace std;
using namespace Eigen;

int polytopeSize;
int *a;
vector<vector<int>> constraints;
int r, c;
int *mat;

Matrix<double, Dynamic, Dynamic> get_mat(int columns) {
    Matrix<double, Dynamic, Dynamic> mmm;
    mmm.resize(r, columns);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < columns; j++) {
            mmm(i, j) = mat[j] & (1 << i);
        }
    }
    return mmm;
}

int compute_det() {
    return get_mat(r).determinant();
}

int compute_rank(int columns) {
    FullPivLU<Matrix<double, Dynamic, Dynamic>> lu_decomp(get_mat(columns));
    return lu_decomp.rank();
}

bool brute(int lvl) {
    if (lvl == c) {
        cout << "f" << endl;
//        cerr << "FOUND" << endl;
        cout << "$ \\begin{pmatrix}" << endl;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << int(bool(a[j] & (1 << i)));
                if (j != c - 1) {
                    cout << " & ";
                } else if (i != r - 1) {
                    cout << "\\\\";
                }
            }
            cout << endl;
        }
        cout << "\\end{pmatrix} $" << endl << "\\\\\\\\" << endl << endl;
        return true;
    }
    for (a[lvl] = 1; a[lvl] < 1 << r; a[lvl]++) {
        bool linearly_dependent = false;
        for (auto &p : constraints) {
            int columns = 0;
            for (auto &x : p) {
                if (x <= lvl) {
                    mat[columns++] = a[x];
                }
            }
            if (columns > 0 && compute_rank(columns) < columns) {
                linearly_dependent = true;
                break;
            }
        }
        if (linearly_dependent) {
            continue;
        }
        if (brute(lvl + 1)) {
            return true;
        }
    }
    return false;
}

bool startSearch(const vector<vector<int>> &polytopeDescription, int rows, int cols) {
    constraints = polytopeDescription;
    mat = new int[polytopeDescription[0].size()];
    r = rows;
    c = cols;
    a = new int[c];
    for (int i = 0; i < r; i++) {
        a[i] = (1 << i);
    }
    return brute(r);
}
