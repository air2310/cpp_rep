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
	unsigned int numsquares = 3;
}; screen mon;

struct settings {
	int refreshrate = 60;

	int triallength = 15; //seconds
	int restlength = 5;
	int cuelength = 1;
	int nblocks = 3;

	double alphalevel = 127.5;

}; settings set;

struct flicktime {

	int trial = set.refreshrate*set.triallength; //seconds
	int rest = set.refreshrate*set.restlength;
	int cue = set.refreshrate*set.cuelength;

}; flicktime f;


struct frequencies {
	std::vector<int> x = { 5, 7, 11, 13, 15 }; // {28.8, 20.57, 13.09, 11.08}
	std::vector<int> y = { 17, 19, 23, 29, 31 }; // {8.47, 7.58, 6.27, 4.97};

	//std::vector<int> x = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }; // 
	//std::vector<int> y = { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 }; //
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

	Gradientx.makesquares(mon.width, mon.height, mon.numsquares);
	Gradienty.makesquares(mon.width, mon.height, mon.numsquares);

	sf::Font courier;
	if (!courier.loadFromFile("cour.ttf"))	{}

	sf::Text restscreen;
	restscreen.setFont(courier); // font is a sf::Font
	restscreen.setCharacterSize(60); // in pixels, not points!
	restscreen.setColor(sf::Color::White);
	restscreen.setPosition(sf::Vector2f(float(mon.width/2)-30, float(mon.height/2)-30)); // absolute position

	cueperiod cue;
	std::vector<int> tilepos = cue.randpos(mon.numsquares);
	sf::RectangleShape cueshape;

	gamesegments currentsegment = gamesegments::rest;
	int framecount = 0;
	int Trial = 1;
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
				sprintf_s(strN, "%d", Trial);
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
				currentsegment = gamesegments::cue;
				int check;
			}

			break;

		case gamesegments::cue:

			if (framecount == 1) {
				cueshape = cue.rendercue(mon.width, mon.height, mon.numsquares, tilepos[Trial]);
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
			}

			if (framecount == 6) {
				trigger(trig.null);
			}

			Gradientx.flick(FLICKSX, framecount, mon.numsquares, 1, flick2use); //x
			Gradienty.flick(FLICKSY, framecount, mon.numsquares, 2, flick2use); //y

			window.clear();
			window.draw(Gradientx);
			window.draw(Gradienty);
			//window.draw(cueshape);

			if (framecount == f.trial - 1) {
				framecount = 0;
				currentsegment = gamesegments::rest;
				if (Trial = mon.numsquares*mon.numsquares) {
					Trial = 1;
					Block++;
				}

				Trial++;

			}

			sf::Time refresh = clock.restart();
			framerate[framecount] = refresh.asMicroseconds();

			break;

		}
		window.display();
	}



	return 0;
}