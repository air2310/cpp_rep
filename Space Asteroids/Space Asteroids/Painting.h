#pragma once

typedef std::vector<int> Row;

std::vector<Row> PreAllocateAst(int nAst, int nFrames, int nWidth, int nHeight, int nShip, int AstSpeed, std::vector<double>& inc);

std::vector<Row> CreateColorCond();

std::vector<Row> ContactMatrix(int nFrames, int nTrials);
