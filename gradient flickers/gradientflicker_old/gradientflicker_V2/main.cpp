#include <SFML/Graphics.hpp>
#include "gradient.h"
#include "flicker.h"
#include <iostream>
#include <math.h>

flicktype flick2use = flicktype::smooth;

struct screen {
	unsigned int width = 1920;
	unsigned int height = 1080;
	unsigned int numsquares = 5;
}; screen mon;

struct settings {
	int refreshrate = 60;

	int triallength = 15; //seconds
	int restlength = 5;
	int cuelength = 1;

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

	//std::vector<int> x = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }; // {28.8, 20.57, 13.09, 11.08}
	//std::vector<int> y = { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 }; // {8.47, 7.58, 6.27, 4.97};
}; frequencies frames;

enum class gamesegments { rest, cue, flick };

sf::RectangleShape rendercue(int width, int height, int numsquares, int i, int j) {

	sf::Vector2f tileSize = { float(width / numsquares)-20, float(height / numsquares)-20 };

	sf::Vector2f cueloc = sf::Vector2f(i * tileSize.x+10, j * tileSize.y+10);

	sf::RectangleShape cue(tileSize);
	cue.setOutlineThickness(10);
	cue.setOutlineColor(sf::Color(0, 255, 0, 255));
	cue.setFillColor(sf::Color(0, 0, 0, 0));
	cue.setPosition(cueloc);
	return cue;
}

int main() {

	gradient Gradientx;
	gradient Gradienty;
	flicker Flicker;
		
	Matrix FLICKSX = Flicker.flickrates(f.trial, frames.x, mon.numsquares, flick2use, set.alphalevel);
	Matrix FLICKSY = Flicker.flickrates(f.trial, frames.y, mon.numsquares, flick2use, set.alphalevel);

	Gradientx.makesquares(mon.width, mon.height, mon.numsquares);
	Gradienty.makesquares(mon.width, mon.height, mon.numsquares);
	

	sf::RenderWindow window(sf::VideoMode(mon.width, mon.height), "GradientFlicker", sf::Style::None);
	//window.setFramerateLimit(set.refreshrate);
	window.setVerticalSyncEnabled(true);

	sf::Font courier;
	if (!courier.loadFromFile("cour.ttf"))	{}

	sf::Text restscreen;
	restscreen.setFont(courier); // font is a sf::Font
	restscreen.setCharacterSize(60); // in pixels, not points!
	restscreen.setColor(sf::Color::White);
	restscreen.setPosition(sf::Vector2f(float(mon.width/2)-30, float(mon.height/2)-30)); // absolute position

	sf::RectangleShape cue;

	gamesegments currentsegment = gamesegments::rest;
	int framecount = 0;
	int Trial = 1;
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
			}
			
			window.clear();
			window.draw(restscreen);
			

			if (framecount == f.rest - 1) {
				Trial++;
				framecount = 0;
				currentsegment = gamesegments::cue;
				int check;
			}
			break;

		case gamesegments::cue:

			cue = rendercue(mon.width, mon.height, mon.numsquares, 1, 3);

			window.clear();
			window.draw(cue);

			if (framecount == f.cue - 1) {
				framecount = 0;
				currentsegment = gamesegments::flick;
			}
			break;

		case gamesegments::flick:
			
			Gradientx.flick(FLICKSX, framecount, mon.numsquares, 1, flick2use); //x
			Gradienty.flick(FLICKSY, framecount, mon.numsquares, 2, flick2use); //y

			window.clear();
			window.draw(Gradientx);
			window.draw(Gradienty);

			if (framecount == f.trial - 1) {
				framecount = 0;
				currentsegment = gamesegments::rest;
			}

			break;

		}
		window.display();
	}



	return 0;
}