#include <iostream>
#include <map>
#include <vector>
#include "eigen/Eigen/LU"
#include <fstream>
#include <algorithm>
#include <set>

#include "io_utils.h"

using namespace std;
using namespace Eigen;

int normalize(double d) {
    int ret = d;
    while (ret < 0) {
        ret += 2;
    }
    while (ret >= 2) {
        ret -= 2;
    }
    return ret;
}

vector<string> normalize(const int &R, const int &C, vector<string> a) {
    Matrix<double, Dynamic, Dynamic> A, B, X;
    A.resize(R, R);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++) {
            A(i, j) = a[i][j] - '0';
        }
    }

    if (abs(A.determinant()) < 0.001) {
        return vector<string>();
    }

    A = A.inverse();
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++) {
            A(i, j) = normalize(A(i, j));
        }
    }
    B.resize(R, C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            B(i, j) = a[i][j] - '0';
        }
    }
    X = A * B;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {

            a[i][j] = normalize(X(i, j)) + '0';

        }
    }

    return a;
}

bool compareVectors(vector<string> a, vector<string> b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool compareVectors(vector<vector<int>> a, vector<vector<int>> b) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> gen(const int &R, const int &C, vector<vector<int>> vect, vector<int> perm) {
    vector<vector<int>> m(C, vector<int>(C, 0));

    for (auto tmp : vect) {
        for (int i = 0; i < tmp.size(); i++) {
            int a = perm[tmp[i]];
            m[a][a]++;
            for (int j = i + 1; j < tmp.size(); j++) {
                int b = perm[tmp[j]];
                m[a][b]++;
                m[b][a]++;
            }
        }
    }
    return m;
}

vector<vector<int>> asdf(const int &R, const int &C, vector<vector<int>> vect) {
    vector<int> p;
    for (int i = 0; i < C; i++) {
        p.push_back(i);
    }
    auto m0 = gen(R, C, vect, p);
    vector<vector<int>> ret;
    while (next_permutation(p.begin(), p.end())) {
        auto m = gen(R, C, vect, p);

        if (compareVectors(m0, m)) {
            ret.push_back(p);
        }
    }
    return ret;
}

void initialize_transofrmations(const int &R, const int &C, map<int, vector<vector<int>>> &t, vector<vector<int>> vect, int idx) {

    fstream fs("/Users/milenkoviclazar/Desktop/asd123.txt", ofstream::app);
    t[idx] = asdf(R, C, vect);
    fs << idx << endl;
    for (int i = 0; i < t[idx].size(); i++) {
        for (int j = 0; j < C; j++) {
            fs << t[idx][i][j];
        }
        fs << endl;
    }
    fs.close();
}

void check47(const int &R, const int &C, vector<vector<string>> a, map<int, vector<vector<int>>> &t, vector<vector<int>> indices, int idx) {

    if (a.size() == 0) {
        return;
    }

    cout << idx << "\\\\" << endl;
    initialize_transofrmations(R, C, t, indices, idx);
    auto tt = t[idx];
    for (int i = 0; i < a.size(); i++) {
        for (int tri = 0; tri < tt.size(); tri++) {
            vector<int> tr = tt[tri];
            vector<string> tmp(a[i]);
            for (int j = 0; j < C; j++) {
                for (int row = 0; row < R; row++) {
                    tmp[row][j] = a[i][row][tr[j]];
                }
            }
            tmp = normalize(R, C, tmp);
            if (tmp.empty()) {
                cout << "FAIL" << endl;
                continue;
            }
            for (int k = 0; k < a.size(); k++) {
                if (k != i && compareVectors(tmp, a[k])) {
                    cout << "pair: " << i << " $\\rightarrow$ " << k << ", transformation:  ";
                    for (int l = 0; l < C; l++) {
                        cout << tr[l];
                    }
                    cout << "\\\\" << endl;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    string basePath = argv[1];
    int C = stoi(argv[2]);
    int R = stoi(argv[3]);
    vector<vector<vector<int>>> indices;
    string hullFileName = basePath + "neighborly" + to_string(C) + "_" + to_string(R) + "inscribed.hull";
    string inputFileName = basePath + "neighborly" + to_string(C) + "_" + to_string(R) + "inscribed.out";

    parseHullFile(indices, hullFileName);

    string s;

    freopen(inputFileName.c_str(), "r", stdin);

    int idx = -1;
    vector<string> current;
    int row = 0;
    vector<vector<string>> mat;
    bool started = false;
    map<int, vector<vector<int>>> transformations;

    while (1) {
        getline(cin, s);

        if (cin.eof()) {
            break;
        }
        if (s.find("polytope") != string::npos) {
            idx++;
            if (idx > 0) {
                mat.erase(mat.begin() + mat.size() - 1);

                check47(R, C, mat, transformations, indices[idx - 1], idx - 1);
            }
            mat.clear();
            mat.push_back(vector<string>());
            started = true;
            continue;
        }
        if (!started) {
            continue;
        }
        if (s.empty()) {
            continue;
        }

        (*mat.rbegin()).push_back(s);
        if ((*mat.rbegin()).size() == R) {
            mat.push_back(vector<string>());
        }
    }
    idx++;
    mat.erase(mat.begin() + mat.size() - 1);

    check47(R, C, mat, transformations, indices[idx - 1], idx - 1);
}