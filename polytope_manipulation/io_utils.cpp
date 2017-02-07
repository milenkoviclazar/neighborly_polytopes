#include "io_utils.h"

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

bool parseHullFile(vector<vector<vector<int>>> &polytopeIndices, const string &hullFileName) {
    fstream fs;
    fs.open(hullFileName, fstream::in);
    if (!fs.good()) {
        cerr << "Bad file name" << endl;
        return false;
    }
    int braceLevel = 0;
    int number = 0;
    do {
        char c;
        fs >> c;
        if (c == '[') {
            braceLevel++;
            if (braceLevel == 1) {
                polytopeIndices.push_back(vector<vector<int>>());
            } else if (braceLevel == 2) {
                polytopeIndices.rbegin()->push_back(vector<int>());
            }
        } else if (c == ']') {
            braceLevel--;
            if (braceLevel == 1) {
                polytopeIndices.rbegin()->rbegin()->push_back(number);
                number = 0;
            }
        } else if (c == ',') {
            if (braceLevel == 2) {
                polytopeIndices.rbegin()->rbegin()->push_back(number);
                number = 0;
            }
        } else if (isdigit(c)) {
            number = 10 * number + c - '0';
        }
    } while (!fs.eof());
    fs.close();
    return true;
}
