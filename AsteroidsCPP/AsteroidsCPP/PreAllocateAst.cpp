#include <vector>
#include <cstdlib>      // std::rand, std::srand
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <math.h>
#include<iostream>


typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;


std::vector<int> getfirstposition(int nAst, int size, int nShip, std::vector<double>& inc) {
	//std::srand(unsigned(std::time(0))); //randomiser

	std::vector<int> firstposition(nAst);

	for (int A = 0; A < nAst; A++) {
		
		firstposition[A] = (rand() % size + 1 - nShip-8);
	}
	return firstposition;
}

std::vector<int> getastpositions(int nFrames, int nAst, int size, int nShip, int A, std::vector<double>& inc) {

	std::vector<int> firstposition = getfirstposition(nAst, size, nShip, inc);

	std::vector<int> astposition(nFrames);

	for (int F = 0; F < nFrames; F++) {
		if (F == 0) {
			astposition[0] = firstposition[A];
		}
		else {
			astposition[F] = astposition[F-1] + floor(inc[A]*100)/100; // firstposition[A]; //inc;

			if (astposition[F] < 8 | astposition[F] > (size-nShip-8)) {
				if (astposition[F] < 8) {
					astposition[F] = (size - nShip-8);
				}
				else {
					astposition[F] = 8;
				}
			}
		}
	}
	return astposition;
}

Matrix PreAllocateAst(int nAst, int nFrames, int nWidth, int nHeight, int nShip, int AstSpeed, std::vector<double>& inc) {
	//std::srand(unsigned(std::time(0))); //randomiser

	Matrix AstX(nAst, Row(nFrames));
	Matrix AstY(nAst, Row(nFrames));


	for (int A = 0; A < nAst; A++) { //get first frame positsion

		
		AstX[A] = getastpositions(nFrames, nAst, nWidth, nShip, A, inc);
		AstY[A] = getastpositions(nFrames, nAst, nWidth, nShip, A, inc);
		
	}

	
		return AstX;


}