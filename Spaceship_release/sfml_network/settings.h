#pragma once

#include <fstream> //ifs
//#include "flicker.h"

bool quit = false;

int result;
int result2use;

flicktype flick2use = flicktype::smooth;

enum class control {
	server, controller, keyboard
};

control movetype = control::controller;

struct screen {
	int width = 1920;
	int height = 1080;

	int xcentre = width / 2;
	int ycentre = height / 2;

	int ref = 60;

}; screen mon;

struct settings {
	int triallength = 60; //seconds

	//float targetsize = 0.6;// 300px
	//int rawtargetsize = 300;// 300px
	float targetsize = 0.4;// 300px
	int rawtargetsize = 300;// 300px

	float obsticlesize = 1;

	int shift = 0;
	int backgroundshift = 0;
	int backgroundshift_rate = 10;
	int backgroundshift2 = 1000;

	double alphalevel = 255;

	int targetpos = std::rand() % 900 + 80;
	int targetpos2 = std::rand() % 900 + 80;

	int numobs = 6;

	bool screenshot = false;
}; settings set;

struct flicktime {
	int trial = mon.ref*set.triallength; //seconds
}; 	flicktime f;

struct frequencies {
	int nHz = 2;
	std::vector<double> Hzintended = { 8, 10 };

	double ref = double(mon.ref);
	std::vector<double> Hzreal = { ref / 8, ref / 10 }; // Hz 11.08 13.09

}; frequencies frames;

std::vector<double> sHz = { 1000 / frames.Hzintended[0] / 1000, 1000 / frames.Hzintended[1] / 1000 };
std::vector<double> fHz = { round(sHz[0] * mon.ref), round(sHz[1] * mon.ref) };

std::vector<double> makeclut(const char* filename) {

	std::vector< double > values;

	std::ifstream ifs(filename);

	double val;
	while (ifs >> val)
		values.push_back(val);

	return values;
}

struct CLUT
{
	std::vector<double> white = makeclut("stim\\CLUT_white_rgb.txt");
}; CLUT clut;