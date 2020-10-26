#include "io_utils.h"

#include <fstream>
#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>

using namespace std;

fstream fs;

string fixPath(string path) {
    if (*path.rbegin() != '/') {
        path += '/';
    }
    return path;
}

vector<int> parse(string s) {
    vector<int> ret;
    stringstream iss(s);
    string val;
    while (getline(iss, val, ',')) {
        ret.push_back(stoi(val));
    }
    return ret;
}

bool openHullFile(const string &hullPath) {
    fs.open(hullPath, fstream::in);
    if (!fs.good()) {
        cerr << "Bad file name" << endl;
        return false;
    }
    return true;
}

void closeStream() {
    fs.close();
}

bool getNextPolytope(vector<vector<int>> &polytope) {
    polytope.clear();
    string line;
    if (getline(fs, line)) {
//        cerr << line << endl;
        int lidx = line.find("[");
        if (lidx == string::npos) {
            closeStream();
            return false;
        }
        int ridx = line.rfind("]");
        stack<char> s;
        string tmp;
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
        return true;
    }
    return false;
}
