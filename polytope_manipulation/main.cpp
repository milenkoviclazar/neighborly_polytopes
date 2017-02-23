#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include <ctime>
#include <fstream>
#include <iostream>
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

    int mpiNodeCount = -1;
    int id = -1;

#ifdef USE_MPI
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiNodeCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
#endif /* USE_MPI */

    string outFileName = outputPath + fileName + to_string((long long int) id) + ".out";
    cerr << outFileName << endl;
    freopen(outFileName.c_str(), "w", stdout);
    clock_t begin = clock();

    openHullFile(hullPath);

    int polytopeIdx = 0;
    vector<vector<int>> polytopeDescription;
    while (getNextPolytope(polytopeDescription)) {
        if ((id == -1) || (polytopeIdx % mpiNodeCount == id)) {
            cout << "polytope " << polytopeIdx << ":" << endl;
            cerr << "polytope " << polytopeIdx << " at node " << id << ":" << endl;
            startSearch(polytopeDescription, r, c);
        }
        polytopeIdx++;
    }

#ifdef USE_MPI
    MPI_Finalize();
#endif /* USE_MPI */

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "elapsed time: " << elapsed_secs << endl;
    cerr << "elapsed time: " << elapsed_secs << endl;
    return 0;
}
