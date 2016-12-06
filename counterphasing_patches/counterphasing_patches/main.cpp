#include <SFML/Graphics.hpp>
#include <iostream>
#include "flicker.h"
#include <fstream> //ifs

double flickstate;

struct screen {
	int width = 1920*2;
	int height = 400;

	int xcentre = width / 2;
	int ycentre = height / 2;

	int ref = 60;
}; screen mon;

struct settings {
	int triallength = 5; //seconds
	float targetsize = 0.6;// 300px
	int rawtargetsize = 300;// 300px
	double alphalevel = 255;

}; settings set;

struct flicktime {
	int trial = mon.ref*set.triallength; //seconds
}; 	flicktime f;

struct positions {
	std::vector<int> x = {mon.xcentre -set.rawtargetsize/2-1920/2, mon.xcentre - set.rawtargetsize / 2 + 1920 / 2 };
	std::vector<int> y = {mon.ycentre - set.rawtargetsize / 2, mon.ycentre - set.rawtargetsize / 2 };

}; positions pos;

struct frequencies {

	std::vector<double> Hzintended = { 8, 10 };

	double ref = double(mon.ref);
	std::vector<double> Hzreal = { ref / 8, ref / 10 }; // Hz 11.08 13.09

}; frequencies frames;

int nHz = 2;
std::vector<double> sHz = { 1000 / frames.Hzintended[0] / 1000, 1000 / frames.Hzintended[1] / 1000 };
std::vector<double> fHz = {round(sHz[0]*mon.ref), round(sHz[1] * mon.ref) };

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


flicktype flick2use = flicktype::smooth;


int main() {

	flicker Flicker;
	Matrix FLICKS = Flicker.flickrates(f.trial, frames.Hzintended, nHz, flick2use, set.alphalevel, mon.ref);

	// ----- sprites 1! -----
	sf::Image TARGET;
	TARGET.loadFromFile("stim\\target1.bmp");
	TARGET.createMaskFromColor(sf::Color(0,0,0));

	sf::Texture TARGET1;
	if (!TARGET1.loadFromImage(TARGET))	{
		std::cout << "error loading target 1" << std::endl;
	}

	sf::Sprite target1;
	target1.setTexture(TARGET1);
	target1.setScale(sf::Vector2f(set.targetsize, set.targetsize));
	
	// ----- sprites 2! -----
	sf::Image TARGETb;
	TARGETb.loadFromFile("stim\\target2.bmp");
	TARGETb.createMaskFromColor(sf::Color(0, 0, 0));

	sf::Texture TARGET2;
	if (!TARGET2.loadFromImage(TARGETb)) {
		std::cout << "error loading target 2" << std::endl;
	}
	sf::Sprite target2;
	target2.setTexture(TARGET2);
	target2.setScale(sf::Vector2f(set.targetsize, set.targetsize));

	// ----- open windows -----
	sf::RenderWindow window1(sf::VideoMode(mon.width, mon.height), "counterphasing_patches Left", sf::Style::None);
	window1.setVerticalSyncEnabled(true);
	window1.setPosition(sf::Vector2i(0, 0));

	sf::RenderWindow window2(sf::VideoMode(mon.width, mon.height), "counterphasing_patches Right", sf::Style::None);
	window2.setVerticalSyncEnabled(true);
	window2.setPosition(sf::Vector2i(0, 680));

	//window.setFramerateLimit(10);

	sf::Clock clock;
	std::vector<double> framerate(f.trial);
	int framecount = 0;

	while (window2.isOpen())
	{
		window1.isOpen();
		sf::Event event;

		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window1.close();
		}
		while (window2.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window2.close();
		}

		// ----- drawing stuff -----
		window1.clear(sf::Color(0,0,0,0));
		window2.clear(sf::Color(0,0,0,0));

		flickstate = FLICKS[0][framecount];
		target1.setColor(sf::Color(0, 0, clut.white[flickstate]));
		flickstate = FLICKS[2][framecount];
		target2.setColor(sf::Color(clut.white[flickstate], 0, 0));
		for (int xpos = 0; xpos < 2; xpos++) {

			target1.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
			target2.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
			window1.draw(target2);
			window1.draw(target1);
		}

		flickstate = FLICKS[1][framecount];
		target1.setColor(sf::Color(0, clut.white[flickstate],0));
		flickstate = FLICKS[3][framecount];
		target2.setColor(sf::Color(clut.white[flickstate], 0, clut.white[flickstate]));
		for (int xpos = 0; xpos < 2; xpos++) {

			target1.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
			target2.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
			window2.draw(target2);
			window2.draw(target1);
		}

		//flickstate = FLICKS[0][framecount];
		//target1.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));
		//flickstate = FLICKS[2][framecount];
		//target2.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));
		//for (int xpos = 0; xpos < 2; xpos++) {

		//	target1.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
		//	target2.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
		//	window1.draw(target2);
		//	window1.draw(target1);
		//}

		//flickstate = FLICKS[1][framecount];
		//target1.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));
		//flickstate = FLICKS[3][framecount];
		//target2.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));
		//for (int xpos = 0; xpos < 2; xpos++) {

		//	target1.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
		//	target2.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
		//	window2.draw(target2);
		//	window2.draw(target1);
		//}


		//for (int xpos = 0; xpos < 2; xpos++) {

		//	flickstate = FLICKS[0][framecount];
		//	target1.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));
		//	flickstate = FLICKS[2][framecount];
		//	target2.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));

		//	target1.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
		//	target2.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
		//	window1.draw(target2);
		//	window1.draw(target1);

		//	flickstate = FLICKS[1][framecount];
		//	target1.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));

		//	target1.setPosition(sf::Vector2f(pos.x[xpos], pos.y[0])); // absolute position
		//	window2.draw(target1);
		//}


		// ----- timing stuff -----
		sf::Time refresh = clock.restart();
		framerate[framecount] = refresh.asMicroseconds();

		framecount++;
		if (framecount > f.trial-1) {
			framecount = 1;
		}

		// ----- display -----
		
		window1.display();
		window2.display();
	}


	return 0;
}