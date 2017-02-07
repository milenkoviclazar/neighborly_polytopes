#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

#include "eigen/Eigen/LU"

using namespace std;
using namespace Eigen;

void checkZn(const vector<string> &matrix, const int &base, const string &fileName, const vector<vector<int>> &polytope, int idx, const int &r, const int &c)
{
    vector<vector<int>> a(r, vector<int>(c));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            a[i][j] = matrix[i][j] - '0';
        }
    }

    Matrix<double, Dynamic, Dynamic> A;
    A.resize(r, r);
    bool allOnes = true;

    for (int v = 0; v < polytope.size(); v++)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < r; j++)
            {
                A(i, j) = a[i][polytope[v][j]];
            }
        }
        int d = int(A.determinant());
        while (d < 0)
        {
            d += base;
        }
        while (d >= base)
        {
            d -= base;
        }
        if (d + 1 != base && d != 1)
        {
            allOnes = false;
        }
    }
    if (allOnes)
    {
        return;
    }
    cerr << "adv" << endl;
    cout << "adv" << endl;
    int row = 0;
    int col = 0;
    while (!allOnes)
    {
        a[row][col + r] = a[row][col + r] + 2;
        while (a[row][col + r] >= base)
        {
            a[row][col + r] -= base;
            col++;
            if (col == c - r)
            {
                col = 0;
                row++;
                if (row == r)
                {
                    break;
                }
            }
            a[row][col + r] += 2;
        }
        if (row == r)
        {
            break;
        }
        row = col = 0;
        /*
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cerr << setw(2) << a[i][j] << " ";
            }
            cerr << endl;
        }
        cerr << endl;
        */
        allOnes = true;
        for (int v = 0; v < polytope.size(); v++)
        {
            for (int i = 0; i < r; i++)
            {
                for (int j = 0; j < r; j++)
                {
                    A(i, j) = a[i][polytope[v][j]];
                }
            }
            int d = int(A.determinant());
            while (d < 0)
            {
                d += base;
            }
            while (d >= base)
            {
                d -= base;
            }
            if (d + 1 != base && d != 1)
            {
                allOnes = false;
            }
        }
    }
    if (row == r)
    {
        cerr << "DIAMONDZ:" << endl;
        cout << "DIAMONDZ:" << endl;
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << setw(2) << a[i][j] << " ";
        }
        cout << endl;
    }

};


void parseRC(string unnedeedFileName, int &r, int &c)
{
    while (unnedeedFileName.find("/") != string::npos)
    {
        unnedeedFileName.erase(unnedeedFileName.begin());
    }
    while (isdigit(*unnedeedFileName.begin()))
    {
        unnedeedFileName.erase(unnedeedFileName.begin());
    }
    while (!isdigit(*unnedeedFileName.begin()))
    {
        unnedeedFileName.erase(unnedeedFileName.begin());
    }
    c = 0;
    while (isdigit(*unnedeedFileName.begin()))
    {
        c = c * 10 + *unnedeedFileName.begin() - '0';
        unnedeedFileName.erase(unnedeedFileName.begin());
    }
    unnedeedFileName.erase(unnedeedFileName.begin());
    r = 0;
    while (isdigit(*unnedeedFileName.begin()))
    {
        r = r * 10 + *unnedeedFileName.begin() - '0';
        unnedeedFileName.erase(unnedeedFileName.begin());
    }
}

void advancedCheck(const std::string &fileName, const vector<vector<vector<int>>> &polytopeIndices)
{
    cerr << "advanced checking" << endl;
    cout << "advanced checking" << endl;
    int r, c;
    parseRC(fileName, r, c);
    fstream fs;
    fs.open(fileName, fstream::in);
    int idx = -1;
    vector<string> binaryMatrix;
    while (!fs.eof())
    {
        string str;
        getline(fs, str);
        if (fs.eof())
        {
            break;
        }
        //cerr << str << endl;
        cout << str << endl;
        if (str.substr(0, 8) == "polytope")
        {
            idx = stoi(str.substr(9));
        }
        bool binary = true;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] != '0' && str[i] != '1')
            {
                binary = false;
                break;
            }
        }
        if (binary)
        {
            binaryMatrix.push_back(str);
        }
        if (str.empty())
        {
            checkZn(binaryMatrix, 40, fileName, polytopeIndices[idx], idx, r, c);
            binaryMatrix.clear();
        }
    }
    cerr << "END OF ADVANCED CHECKING" << endl;
    cout << "END OF ADVANCED CHECKING" << endl;
    fs.close();
}

