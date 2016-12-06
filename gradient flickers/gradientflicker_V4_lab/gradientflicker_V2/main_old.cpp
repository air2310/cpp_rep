#include <SFML/Graphics.hpp>
#include "gradient.h"
#include "flicker.h"
#include "cueperiod.h"
#include <iostream>
#include <math.h>
#include "triggers.h"

flicktype flick2use = flicktype::smooth;

struct screen {
	unsigned int width = 1920;
	unsigned int height = 1080;
	unsigned int xxtra = round((width - height) / 2);
	unsigned int numsquares = 2;
}; screen mon;

struct settings {
	int refreshrate = 144;

	int triallength = 1; //seconds
	int restlength = 1;
	int cuelength = 1;
	int nblocks = 26;

	double alphalevel = 255/2;

}; settings set;

struct flicktime {

	int trial = set.refreshrate*set.triallength; //seconds
	double rest = set.refreshrate*set.restlength;
	int cue = set.refreshrate*set.cuelength;

}; flicktime f;


struct frequencies {

	std::vector<double> x = { 11, 13 }; // Hz
	std::vector<double> y= { 17, 19 }; // Hz

	//std::vector<double> xraw = { 11, 13 }; // Hz
	//std::vector<double> yraw = { 17, 19 }; // Hz

	//std::vector<double> F(std::vector<double> raw) {
	//	std::vector<double> F(mon.numsquares);
	//		for (int i = 0; i < mon.numsquares; i++) {
	//			double freq = raw[i];
	//			F[i] = double(set.refreshrate)/ freq;
	//			std::cout << F[i] << std::endl;
	//		}
	//	return F;
	//}

	//std::vector<double> x = F(xraw);
	//std::vector<double> y = F(yraw);

	

}; frequencies frames;


struct triggers {
	int rest = 100;
	int cue = 101;
	int null = 0;

}; triggers trig;

enum class gamesegments { rest, cue, flick };


std::vector<int> randpos(int numsquares) {
	std::vector<int> randpos(numsquares*numsquares);
	for (int i = 0; i < numsquares*numsquares; ++i) {
		randpos[i] = i;
	}
	std::srand(unsigned(std::time(0))); //randomiser
	std::random_shuffle(randpos.begin(), randpos.end(), myrandom); //randomly shuffle elements
	return randpos;
}




int main() {

	gradient Gradientx;
	gradient Gradienty;
	flicker Flicker;
		
	Matrix FLICKSX = Flicker.flickrates(f.trial, frames.x, mon.numsquares, flick2use, set.alphalevel);
	Matrix FLICKSY = Flicker.flickrates(f.trial, frames.y, mon.numsquares, flick2use, set.alphalevel);

	Gradientx.makesquares(mon.height, mon.height, mon.numsquares, mon.xxtra);
	Gradienty.makesquares(mon.height, mon.height, mon.numsquares, mon.xxtra);

	sf::Font courier;
	if (!courier.loadFromFile("cour.ttf"))	{}

	sf::Text restscreen;
	restscreen.setFont(courier); // font is a sf::Font
	restscreen.setCharacterSize(60); // in pixels, not points!
	restscreen.setColor(sf::Color::White);
	restscreen.setPosition(sf::Vector2f(float(mon.width/2)-30, float(mon.height/2)-30)); // absolute position

	cueperiod cue;
	std::vector<double> tilepos = cue.randpos(mon.numsquares);
	sf::CircleShape cueshape;

	gamesegments currentsegment = gamesegments::rest;
	int framecount = 0;
	int Trial = 0;
	int Block = 1;

	sf::RenderWindow window(sf::VideoMode(mon.width, mon.height), "GradientFlicker", sf::Style::None);
	//window.setFramerateLimit(set.refreshrate);
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;
	std::vector<double> framerate(f.trial);

	while (window.isOpen())
	{
		
		//std::cout << framecount << ';';
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		framecount++;

		switch (currentsegment) {

		case gamesegments::rest:

			if (framecount == 1) {
				char strN[3];	memset(strN, '\0', sizeof(strN));
				sprintf_s(strN, "%d", Block);
				restscreen.setString(strN);

				trigger(trig.rest);
			}

			if (framecount == 6) {
				trigger(trig.null);
			}
			
			window.clear();
			window.draw(restscreen);
			

			if (framecount == f.rest - 1) {
				framecount = 0;
				currentsegment = gamesegments::flick;
				int check;
			}

			break;

		case gamesegments::cue:

			if (framecount == 1) {
				cueshape = cue.rendercuedot(mon.height, mon.height, mon.numsquares, tilepos[Trial], mon.xxtra);
				trigger(trig.rest);
			}

			if (framecount == 6) {
				trigger(trig.null);
			}

			window.clear();
			window.draw(cueshape);

			if (framecount == f.cue - 1) {
				framecount = 0;
				currentsegment = gamesegments::flick;

				sf::Time refresh = clock.restart();
			}

			break;

		case gamesegments::flick:
			
			if (framecount == 1) {
				trigger(Trial);
				cueshape = cue.rendercuedot(mon.height, mon.height, mon.numsquares, tilepos[Trial], mon.xxtra);
			}

			if (framecount == 6) {
				trigger(trig.null);
			}

			Gradientx.flick(FLICKSX, framecount, mon.numsquares, 1, flick2use); //x
			Gradienty.flick(FLICKSY, framecount, mon.numsquares, 2, flick2use); //y

			window.clear();
			window.draw(Gradienty);
			window.draw(Gradientx);
			window.draw(cueshape);

			
			if (framecount == f.trial - 1) {
				framecount = 0;
				
				if (Trial == mon.numsquares*mon.numsquares-1) {
					if (Block == set.nblocks) {

						event.type = sf::Event::Closed;
					}
					Trial = -1;

					/*char strN[3];	memset(strN, '\0', sizeof(strN));
					sprintf_s(strN, "%d", Block);*/

					char* file = "Tileorder.mat";
					char* varname = "tileorder";
					int matsave = matcreate(file, tilepos, mon.numsquares*mon.numsquares, varname);

					tilepos = cue.randpos(mon.numsquares);
					Block++;
					currentsegment = gamesegments::rest;
					
				}

				char* file = "framerateGF.mat";
				char* varname = "framerate";
				int matsave = matcreate(file, framerate, f.trial, varname);

				std::cout << Trial << std::endl;
				Trial += 1;
				

			}

			sf::Time refresh = clock.restart();
			framerate[framecount] = refresh.asMicroseconds();

			break;

		}
		window.display();
	}



	return 0;
}