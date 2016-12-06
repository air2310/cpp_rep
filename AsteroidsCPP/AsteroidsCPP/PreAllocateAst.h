#pragma once
#include <vector>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

std::vector<Row> PreAllocateAst(int nAst, int nFrames, int nWidth, int nHeight, int nShip, int AstSpeed, std::vector<double>& inc);

