//
// Created by Lazar Milenkovic on 2/6/17.
//

#ifndef ND_CONVEX_HULL_IO_UTILS_H_H
#define ND_CONVEX_HULL_IO_UTILS_H_H

#include <vector>
#include <string>

bool openHullFile(const std::string &hullPath);
bool getNextPolytope(std::vector<std::vector<int>> &polytope);
std::string fixPath(std::string path);
#endif //ND_CONVEX_HULL_IO_UTILS_H_H
