#pragma once
#include <fstream>
#include <vector>

void inittxt() {

	std::ofstream outLum("data\\timing144_100.txt");
	outLum << "frame" << '\t' << "framerate" << std::endl;
	outLum.close();

}

void writetxt(int FF, std::vector<float> framerate, int nFrames) {

	std::ofstream outLum;
	outLum.open("data\\timing144_100.txt", std::ios_base::app);

		for (int i = 0; i < (nFrames); i++) {
			outLum << i << '\t' << framerate[i] 
				<< '\n';
		}
		outLum << std::endl;

	outLum.close();

}
