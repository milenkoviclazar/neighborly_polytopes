#include <iostream>
#include <vector>

#include "io_utils.h"

using namespace std;

int polytopeSize;
int *a;
vector<vector<int>> constraints;
int r, c;
int *mat;

int compute_rank(int number_of_rows) {
    int row, col;
    for (row = 0, col = 0; row < columns && col < r; col++) {
        for (int i = row; i < columns; i++) {
            if (mat[i] & (1 << col)) {
                swap(mat[i], mat[row]);
            }
        }
        if ((mat[row] & (1 << col)) == 0) {
            continue; // try the next column
        }
        for (int i = row + 1; i < columns; i++) {
            if (mat[i] & (1 << col)) {
                mat[i] ^= mat[row];
            }
        }
        row++;
    }
    return row;
}

bool brute(int lvl) {
    if (lvl == c) {
        cout << "f" << endl;
        cerr << "FOUND" << endl;
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
            if (compute_rank(columns) < columns) {
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
