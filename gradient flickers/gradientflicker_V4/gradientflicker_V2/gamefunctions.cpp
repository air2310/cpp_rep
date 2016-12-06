#include <fstream>
#include <vector>
#include <Windows.h>
#include <iostream>
#include "gamefunctions.h"

bool gamestarter(bool startgame, int framecount) {
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000)) {
		std::cout << "starting!" << std::endl;
		startgame = true;
	}
	return startgame;
}

std::vector<double> makeclut(const char* filename) {

	std::vector< double > values;

	std::ifstream ifs(filename);

	double val;
	while (ifs >> val)
		values.push_back(val);

	return values;
}
