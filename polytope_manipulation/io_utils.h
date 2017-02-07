//
// Created by Lazar Milenkovic on 2/6/17.
//

#ifndef ND_CONVEX_HULL_IO_UTILS_H_H
#define ND_CONVEX_HULL_IO_UTILS_H_H

#include <vector>
#include <string>

bool parseHullFile(std::vector<std::vector<std::vector<int>>> &polytopeIndices, const std::string &hullFileName);
#endif //ND_CONVEX_HULL_IO_UTILS_H_H
