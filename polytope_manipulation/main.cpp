#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include "baralic.h"
#include "io_utils.h"
//#include "mpi.h"

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

    cerr << polytopeIndices.size() << " polytopes in total" << endl;
    cerr << "BRUTE" << endl;

    int nodeCount = polytopeIndices.size();
    int id = 0;
//    MPI_Init(NULL, NULL);
//    MPI_Comm_size(MPI_COMM_WORLD, &nodeCount);
//    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    for (int p = 0; p < polytopeIndices.size(); p++) {
        if (p % nodeCount == id) {
            cout << "polytope " << p << ":" << endl;
            cerr << "polytope " << p << " at node " << id << ":" << endl;
            vector<int> a(r, 0);
            brute(polytopeIndices[p], a, 0, r, c);
        }
    }
    cerr << "END OF BRUTE" << endl;
//    MPI_Finalize();
    return 0;
}
