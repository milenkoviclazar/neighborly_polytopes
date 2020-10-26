#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

#include "eigen/Eigen/LU"
#include "io_utils.h"

using namespace std;
using namespace Eigen;

void checkZn(const vector<string> &matrix, const int &base, const vector<vector<int>> &polytope,
             int idx, const int &r, const int &c) {
    vector<vector<int>> a(r, vector<int>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            a[i][j] = matrix[i][j] - '0';
        }
    }

    Matrix<double, Dynamic, Dynamic> A;
    A.resize(r, r);
    bool allOnes = true;

    for (int v = 0; v < polytope.size(); v++) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r; j++) {
                A(i, j) = a[i][polytope[v][j]];
            }
        }
        int d = int(A.determinant());
        while (d < 0) {
            d += base;
        }
        while (d >= base) {
            d -= base;
        }
        if (d + 1 != base && d != 1) {
            allOnes = false;
        }
    }
    if (allOnes) {
        return;
    }
    cerr << "adv" << endl;
    cout << "adv" << endl;
    int row = 0;
    int col = 0;
    while (!allOnes) {
        a[row][col + r] = a[row][col + r] + 2;
        while (a[row][col + r] >= base) {
            a[row][col + r] -= base;
            col++;
            if (col == c - r) {
                col = 0;
                row++;
                if (row == r) {
                    break;
                }
            }
            a[row][col + r] += 2;
        }
        if (row == r) {
            break;
        }
        row = col = 0;
        allOnes = true;
        for (int v = 0; v < polytope.size(); v++) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    A(i, j) = a[i][polytope[v][j]];
                }
            }
            int d = int(A.determinant());
            while (d < 0) {
                d += base;
            }
            while (d >= base) {
                d -= base;
            }
            if (d + 1 != base && d != 1) {
                allOnes = false;
            }
        }
    }
    if (row == r) {
        cerr << "DIAMONDZ:" << endl;
        cout << "DIAMONDZ:" << endl;
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << setw(2) << a[i][j] << " ";
        }
        cout << endl;
    }
};


vector<vector<vector<int>>> polytopeIndices;

int main(int argc, char *argv[]) {
    string inputPath = argv[1];
    if (*inputPath.rbegin() != '/') {
        inputPath += '/';
    }
    string hullPath = argv[2];
    if (*hullPath.rbegin() != '/') {
        hullPath += '/';
    }

    int c = stoi(argv[3]);
    int r = stoi(argv[4]);

    ostringstream oss;
    oss << "neighborly" << c << "_" << r << "inscribed";
    string fileName = oss.str();
    string inputFileName = inputPath + fileName + ".out";
    string hullFileName = hullPath + fileName + ".hull";

    openHullFile(hullFileName);

    vector<vector<int>> polytopeDescription;
    while (getNextPolytope(polytopeDescription)) {
        polytopeIndices.push_back(polytopeDescription);
    }

    fstream fs;
    fs.open(inputFileName, fstream::in);
    int idx = -1;
    vector<string> binaryMatrix;
    while (!fs.eof()) {
        string str;
        getline(fs, str);
        if (fs.eof()) {
            break;
        }
        str.pop_back();
        if (str.find("polytope") != string::npos) {
            cout << str << endl;
            idx++;
        }
        bool binary = true;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] != '0' && str[i] != '1') {
                binary = false;
                break;
            }
        }
        if (binary) {
            binaryMatrix.push_back(str);
        }
        if (str.empty()) {
            checkZn(binaryMatrix, 8, polytopeIndices[idx], idx, r, c);
            binaryMatrix.clear();
        }
    }
    cerr << "END OF ADVANCED CHECKING" << endl;
    cout << "END OF ADVANCED CHECKING" << endl;
    fs.close();
    return 0;
}

