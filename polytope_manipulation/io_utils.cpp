#include "io_utils.h"

#include <fstream>
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

vector<int> parse(string s) {
    vector<int> ret;
    stringstream iss(s);
    string val;
    while (getline(iss, val, ',')) {
        ret.push_back(stoi(val));
    }
    return ret;
}

bool parseHullFile(vector<vector<vector<int>>> &polytopeIndices, const string &hullFileName) {
    fstream fs;
    fs.open(hullFileName, fstream::in);
    if (!fs.good()) {
        cerr << "Bad file name" << endl;
        return false;
    }
    string line;
    while (getline(fs, line)) {
        int lidx = line.find("[");
        if (lidx == string::npos) {
            continue;
        }
        int ridx = line.rfind("]");
        stack<char> s;
        string tmp;
        vector<vector<int>> polytope;
        for (int i = lidx + 1; i < ridx; i++) {
            if (line[i] == ']') {
                while (s.top() != '[') {
                    tmp += s.top();
                    s.pop();
                }
                reverse(tmp.begin(), tmp.end());
                polytope.push_back(parse(tmp));
                tmp.clear();
            } else {
                s.push(line[i]);
            }
        }
        polytopeIndices.push_back(polytope);
    } while (!fs.eof());
    return true;
}
