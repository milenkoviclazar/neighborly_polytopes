#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include <ctime>
#include "baralic.h"
#include "io_utils.h"

#ifdef USE_MPI
#include "mpi.h"
#endif /* USE_MPI */

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

    vector<vector<vector<int>>> polytopeIndices;
    if (!parseHullFile(polytopeIndices, hullPath)) {
        return 0;
    }

    cerr << polytopeIndices.size() << " polytopes in total" << endl;
    cerr << "BRUTE" << endl;

    int nodeCount = polytopeIndices.size();
    int id = -1;

#ifdef USE_MPI
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nodeCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
#endif /* USE_MPI */

    string outFileName = outputPath + fileName + to_string((long long int) id) + ".out";
    cerr << outFileName << endl;
    freopen(outFileName.c_str(), "w", stdout);
    clock_t begin = clock();
    for (int p = 0; p < polytopeIndices.size(); p++) {
        if ((id == -1) || (p % nodeCount == id)) {
            cout << "polytope " << p << ":" << endl;
            cerr << "polytope " << p << " at node " << id << ":" << endl;
            vector<int> a(r, 0);
            brute(polytopeIndices[p], a, 0, r, c);
        }
    }
    cerr << "END OF BRUTE" << endl;

#ifdef USE_MPI
    MPI_Finalize();
#endif /* USE_MPI */

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "elapsed time: " << elapsed_secs << endl;
    return 0;
}
