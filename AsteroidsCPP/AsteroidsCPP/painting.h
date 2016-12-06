#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <vector>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

//typedef struct
//{
//	int H;
//	int D;
//} Pointstruct;


std::vector<Row> PreAllocateAst(int nAst, int nFrames, int nWidth, int nHeight, int nShip, int AstSpeed, std::vector<double>& inc);

std::vector<Row> CreateColorCond();

std::vector<Row> CreateFlicker(int nFrames, int nFreqs, std::vector<int> Freqs, int Refresh);

void cue(HDC hdc, HWND hWnd, int nWidth, int nShip, int nHeight, int xxtra, int border, std::vector<Row>& ColorCond, int Trial, std::vector<int> Order);

int Trial(HDC hdc, HWND hWnd, int nWidth, int nShip, int nHeight, int xxtra, int border, int flicktime, int nFrames, int nAst, std::vector<Row> AstX, std::vector<Row> AstY, std::vector<Row>& ColorCond, int Trial, std::vector<int> Order, std::vector<Row>& Flicker);

void Feedback(HDC hdc, HWND hWnd, int points, int nWidth, int nShip, int nHeight, int xxtra, int border, std::vector<Row>& ColorCond, int Trial, std::vector<int> Order);

//Pointstruct structures();