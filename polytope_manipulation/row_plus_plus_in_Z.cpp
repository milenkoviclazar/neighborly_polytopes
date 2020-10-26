/*
 * Used to check the matrices with added rows in Z (not in Z_2).
 */

#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include "search_plus_plus_Z.h"
#include "io_utils.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cerr << "Invalid number of arguments" << endl;
        return 0;
    }
    string basePath = argv[1];
    if (*basePath.rbegin() != '/') {
        basePath += '/';
    }
    string outputPath = argv[2];
    if (*outputPath.rbegin() != '/') {
        outputPath += '/';
    }
    int c = stoi(argv[3]);
    int r = stoi(argv[4]);

    ostringstream oss;
    oss << "neighborly" << c << "_" << r << "inscribed";
    string fileName = oss.str();
    string hullPath = basePath + fileName + ".hull";
    string solutionPath = basePath + fileName + ".solved";
    int mpiNodeCount = -1;
    int id = -1;

    fstream solFs;
    solFs.open(solutionPath, fstream::in);
    int solutionCnt;
    set<int> solutions;
    solFs >> solutionCnt;
    for (int i = 0; i < solutionCnt; i++) {
        int xxx;
        solFs >> xxx;
        solutions.insert(xxx);
    }
    string outFileName = outputPath + fileName + to_string((long long int) id) + ".tex";
    freopen(outFileName.c_str(), "w", stdout);
    clock_t begin = clock();

    openHullFile(hullPath);
    int polytopeIdx = 0;
    vector<vector<int>> polytopeDescription;
    cout << "\\documentclass{article}\n"
            "\\usepackage{amsmath}\n"
            "\\usepackage[landscape, margin=7mm,a4paper]{geometry}\n"
            "\n"
            "\\begin{document}" << endl;
    cout << "\\begin{center}" << endl;
    cout << "{\\LARGE neighborly " << c << " " << r << " inscribed }" << "\\\\" << endl;
    cout << "$^*$ ozna\\v{c}ava one koji su imali re\\v{s}enje u manjoj dimenziji";
    cout << "\\end{center}" << endl;

    while (getNextPolytope(polytopeDescription)) {
        if (polytopeIdx % 1000 == 0) {
            cerr << polytopeIdx << endl;
        }
        if ((id == -1) || (polytopeIdx % mpiNodeCount == id)) {

            cout << "polytope " << polytopeIdx;
            if (solutions.count(polytopeIdx)) {
                cout << "*";
            }
            cout << endl;
            cout << ": \\\\" << endl;
            for (int i = 0; i < polytopeDescription.size(); i++) {
                if (i % 20 == 0) {
                    cout << "\\\\" << endl;
                }
                cout << "\\lbrack";
                for (int j = 0; j < polytopeDescription[i].size(); j++) {
                    cout << polytopeDescription[i][j];
                    if (j + 1 < polytopeDescription[i].size()) {
                        cout << ",";
                    }
                }
                cout << "\\rbrack";
                if (i + 1 < polytopeDescription.size()) {
                    cout << ",";
                }
            }
            cout << "\\\\\\\\" << endl;
            if (r + 1 <= c && startSearch(polytopeDescription, r + 1, c)) {
//                cout << "f" << endl;
            } else if (r + 2 <= c && startSearch(polytopeDescription, r + 2, c)) {
//                cout << "f " << polytopeIdx << endl;
            } else {
                cout << "n " << polytopeIdx << endl;
                cerr << "NOT NOT NOT NOT NOT NOT\n" << endl;
            }

        }
        polytopeIdx++;
    }


    cout << "\\end{document}" << endl;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cerr << "elapsed time: " << elapsed_secs << endl;
    return 0;
}
