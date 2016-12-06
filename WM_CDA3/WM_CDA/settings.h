#pragma once

double pi = 3.1415926535;
int myrandom(int i) { return std::rand() % i; }

// RandomlySeededMersenneTwister
#include <random>
static std::random_device rd;
static std::mt19937 rng(rd());

enum class trialperiod {
	rest, trial
};


struct screen {
	sf::VideoMode size = sf::VideoMode::getDesktopMode();

	float width = float(size.width);
	float height = float(size.height);

	float xcentre = width / 2;
	float ycentre = height / 2;

	int ref = 60;

}; screen mon;

struct TIMING { //milliseconds

	float cue = 500;
	float interval1_min = 300;
	float interval1_max = 400;
	float memory_array = 100;
	float interval2 = 900;
	float test_array = 2000;

	float trial = cue + interval1_max + memory_array + interval2 + test_array;

	float blockrest = 10;
}; TIMING timing;

struct flicktime {
	float trial = mon.ref*(timing.trial + 2); //seconds

}; 	flicktime f;


struct general {

	sf::Vector2f boxsize = sf::Vector2f(29, 29);
	sf::Vector2f boxcentre = sf::Vector2f(boxsize.x / 2, boxsize.y / 2);

	sf::Vector2f stimspace_size = sf::Vector2f(159, 265);
	sf::Vector2f stimspace_centre = sf::Vector2f(stimspace_size.x/2, stimspace_size.y / 2);
	float stimspace_offset = 124;
	

	float setsize = 8;

	float numtrials_persetsize = 160; //per cell
	float numsets = 3;

	float numcuetypes = 2;

	float numtrials_total = numtrials_persetsize * numsets * numcuetypes;

	float numblocks = 24;
	float numtrials_block = numtrials_total / numblocks;


	bool triggers = false;

	std::vector<sf::Color> colours2use = {
		sf::Color(0, 0, 0),
		sf::Color(255, 0, 0),
		sf::Color(0, 255, 0),
		sf::Color(0, 0, 255),
		sf::Color(255, 255, 0),
		sf::Color(255, 0, 255),
		sf::Color(255, 255, 255)
	};

	float numcols = 7;
	float arrowoffset = 29 ;
	float mindist = 52;

	bool opt_triggers = false;

	bool autoblockprogress = false;

	bool debug;
}; general set;



