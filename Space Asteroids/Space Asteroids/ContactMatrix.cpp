#include <vector>
#include <cstdlib>      // std::rand, std::srand
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <math.h>
#include<iostream>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

Matrix ContactMatrix(int nFrames, int nTrials) {
	Matrix Contact(nTrials, Row(nFrames));

	for (int T = 0; T < nTrials; T++) { 
		for (int F = 0; F < nFrames; F++) {
			Contact[T][F] = 0;
		}
	}
	return Contact;
}