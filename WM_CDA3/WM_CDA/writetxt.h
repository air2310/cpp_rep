#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include <fstream>
//#include <time.h> 
#include <direct.h>

char* uscore = "_";
char* filetype = ".txt";
char* slash = "\\";

std::vector<char*> createPid() {
	std::vector<char*> Pid = { "P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9",
								"P10", "P11", "P12", "P13", "P14", "P15", "P16", "P17", "P18", "P19", 
								"P20", "P21", "P22", "P23", "P24", "P25", "P26", "P27", "P28", "P29" };
	return Pid;
}

std::vector<char*> createPidDir() {
	std::vector<char*> Pid = { "data\\P0\\", "data\\P1\\", "data\\P2\\", "data\\P3\\", "data\\P4\\", "data\\P5\\", "data\\P6\\", "data\\P7\\", "data\\P8\\", "data\\P9\\",
							"data\\P10\\",  "data\\P11\\", "data\\P12\\", "data\\P13\\", "data\\P14\\", "data\\P15\\", "data\\P16\\", "data\\P17\\", "data\\P18\\", "data\\P19\\",
							"data\\P20\\",  "data\\P21\\", "data\\P22\\", "data\\P23\\", "data\\P24\\", "data\\P25\\", "data\\P26\\", "data\\P27\\", "data\\P28\\", "data\\P29\\" };
	return Pid;
}

#include <string>;
//#define _CRT_SECURE_NO_WARNINGS 1
std::string makefilename(char* dataDirect, char* fname, char* ID) {

	char* str = new char[70];
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);

	localtime_s(&timeinfo, &rawtime);

	strftime(str, 100, "%I-%M%p_%F", &timeinfo);

	std::string a(dataDirect);
	std::string b(ID);
	std::string c(uscore);
	std::string d(fname);
	std::string e(uscore);
	std::string f(str);
	std::string g(filetype);
	std::string file2save = a+b+c+d+e+f+g;

	std::cout << "	" << file2save << '\n';

	return file2save;
}

BOOL DirectoryExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void makedirectory(char* dirID) {

	bool exists = DirectoryExists(dirID);
	if (exists == false) {
		_mkdir(dirID);
	}

}

void writetxt(std::vector<std::vector<sf::Vector2f>> all_coordinates, std::vector<std::vector<int>> all_colours,
	std::vector<int> trialtype, std::vector<int> cuedside, std::vector<int> probefidelity_cued, std::vector<int> probefidelity_uncued,
	std::vector<int> left_probeorder, std::vector<int> right_probeorder, std::vector<int> blocktrials, std::vector<int> cuetype_all, char* ID, char* dataDirect) {

	//setup saving
	makedirectory(dataDirect);

	// Xcoord data
	std::string filename = makefilename(dataDirect, "Xcoorddata", ID);

	std::ofstream outx(filename);
	outx << "L1" << '\t' << "L2" << '\t' << "L3" << '\t' << "L4" << '\t' << "R1" << '\t'
		<< "R2" << '\t' << "R3" << '\t' << "R4" << '\t' << std::endl;

	for (int t = 0; t < set.numtrials_total; t++) {
		for (int cc = 0; cc < set.setsize; cc++) {
			sf::Vector2f coord = all_coordinates[t][cc];
			outx << int(coord.x)
				<< '\t';
		}
		outx << std::endl;
	}
	outx.close();

	// Ycoord data
	filename = makefilename(dataDirect, "Ycoorddata", ID);
	std::ofstream outy(filename);
	outy << "L1" << '\t' << "L2" << '\t' << "L3" << '\t' << "L4" << '\t' << "R1" << '\t'
		<< "R2" << '\t' << "R3" << '\t' << "R4" << '\t' << std::endl;

	for (int t = 0; t < set.numtrials_total; t++) {
		for (int cc = 0; cc < set.setsize; cc++) {
			sf::Vector2f coord = all_coordinates[t][cc];
			outy << int(coord.y)
				<< '\t';
		}
		outy << std::endl;
	}
	outy.close();

	//Colours
	filename = makefilename(dataDirect, "Colours", ID);
	std::ofstream outC(filename);
	outC << "L1" << '\t' << "L2" << '\t' << "L3" << '\t' << "L4" << '\t' << "R1" << '\t'
		<< "R2" << '\t' << "R3" << '\t' << "R4" << '\t' << std::endl;

	for (int t = 0; t < set.numtrials_total; t++) {
		for (int cc = 0; cc < set.setsize; cc++) {
			int colournum = all_colours[t][cc];
			outC << int(colournum)
				<< '\t';
		}
		outC << std::endl;
	}
	outC.close();

	//Trialtype (1 = 1col, 2 = 4samecol, 3 = 4uniquecols)
	filename = makefilename(dataDirect, "Trialtype", ID);
	std::ofstream outT(filename);
	outT << "1Col" << '\t' << "2Cols" << '\t' << "4Cols" << '\t' << std::endl;
	for (int t = 0; t < set.numtrials_total; t++) {
		outT << int(trialtype[t])
			<< std::endl;
	}
	outT.close();

	// cuedside (1 = left, 2 = right)
	filename = makefilename(dataDirect, "Cuedside", ID);
	std::ofstream outCu(filename);

	for (int t = 0; t < set.numtrials_total; t++) {
		outCu << int(cuedside[t])
			<< std::endl;
	}
	outCu.close();

	// Probe fidility ( cued and uncued side - 1 = col was present, 2 = col was absent )
	filename = makefilename(dataDirect, "Probefidelity", ID);
	std::ofstream outP(filename);

	outP << "Cued" << '\t' << "Uncued" << '\t' << std::endl;
	for (int t = 0; t < set.numtrials_total; t++) {
		outP << int(probefidelity_cued[t]) << '\t' << int(probefidelity_uncued[t])
			<< std::endl;
	}
	outP.close();

	// Probed colour (Left and right)
	filename = makefilename(dataDirect, "ProbedCols", ID);
	std::ofstream outPc(filename);

	outPc << "Left" << '\t' << "Right" << '\t' << std::endl;
	for (int t = 0; t < set.numtrials_total; t++) {
		outPc << int(left_probeorder[t]) << '\t' << int(right_probeorder[t])
			<< std::endl;
	}
	outPc.close();

	//CueType (Global and Local)
	filename = makefilename(dataDirect, "ProbeType", ID);
	std::ofstream outQ(filename);

	outQ << "global V local probe" << '\t' << std::endl;
	for (int t = 0; t < set.numtrials_total; t++) {
		outQ << int(cuetype_all[t]) 
			<< std::endl;
	}
	outQ.close();

}