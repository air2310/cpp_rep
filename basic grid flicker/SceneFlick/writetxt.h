#pragma once
#include <fstream>


void inittxt() {

	std::ofstream outLum("data\\luminancestc2.txt");
	outLum << "frame" << '\t' << "frequency" << '\t' << "phase" << '\t' << "framerate" << '\t' << "luminance" << std::endl;
	outLum.close();

}

void writetxt(int FF, std::vector<float> framerate, std::vector<float> luminance, std::vector<float> frequencies, std::vector<float> phases, int nFrames) {

	std::ofstream outLum;
	outLum.open("data\\luminancestc2.txt", std::ios_base::app);

		for (int i = 0; i < (nFrames+60); i++) {
			outLum << i << '\t' << frequencies[FF] << '\t' << phases[FF] << '\t' << framerate[i] << '\t' << luminance[i]
				<< '\n';
		}
		outLum << std::endl;

	outLum.close();

}
