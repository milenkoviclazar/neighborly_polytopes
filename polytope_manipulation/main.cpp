#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include "baralic.h"
#include "io_utils.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Invalid number of arguments" << endl;
        return 0;
    }
    string basePath = argv[1];
    int c = stoi(argv[2]);
    int r = stoi(argv[3]);

    ostringstream oss;
    oss << "neighborly" << c << "_" << r << "inscribed";
    string fileName = basePath + oss.str();
    string hullFileName = fileName + ".hull";
    string outFileName = fileName + ".out";

    //freopen(outFileName.c_str(), "w", stdout);
    vector<vector<vector<int>>> polytopeIndices;
    if (!parseHullFile(polytopeIndices, hullFileName)) {
        return 0;
    }
    cout << polytopeIndices.size() << endl;
    calculate(polytopeIndices, r, c);
    return 0;
}
