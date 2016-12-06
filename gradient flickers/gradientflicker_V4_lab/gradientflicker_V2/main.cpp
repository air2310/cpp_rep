#include <SFML/Graphics.hpp>
#include "gradient.h"
#include "flicker.h"
#include "cueperiod.h"
#include "gamefunctions.h"
#include <iostream>
#include "triggers.h"
#include <Windows.h>

flicktype flick2use = flicktype::smooth;

struct screen {
	unsigned int width = 1920;
	unsigned int height = 1080;
	unsigned int xxtra = round((width - height) / 2);
	unsigned int numsquares = 2;
}; screen mon;

struct settings {
	int refreshrate = 144;

	int triallength = 5; //seconds
	int restlength = 1;
	int cuelength = 1;
	int nblocks = 93; //32 per type

	double alphalevel = 255;

}; settings set;

struct flicktime {

	int trial = set.refreshrate*set.triallength; //seconds
	double rest = set.refreshrate*set.restlength;
	int cue = set.refreshrate*set.cuelength;

}; flicktime f;


struct frequencies {

	std::vector<double> x = { 11, 13 }; // Hz 11 13
	std::vector<double> y= { 17, 19 }; // Hz 17 19

	std::vector<double> xreal = { 144/13, 144/11 }; // Hz 11.08 13.09
	std::vector<double> yreal = { 144/9, 144/8 }; // Hz 16 18

}; frequencies frames;


struct triggers {
	int rest = 255;
	int cue = 254;
	int null = 0;

}; triggers trig;


int main() {

	gradient Gradientx;
	gradient Gradienty;
	gradient GradientA;
	flicker Flicker;
	
	Matrix FLICKSX;
	Matrix FLICKSY;

	Matrix FLICKSXimag = Flicker.flickrates(f.trial, frames.x, mon.numsquares, flick2use, set.alphalevel, set.refreshrate);
	Matrix FLICKSYimag = Flicker.flickrates(f.trial, frames.y, mon.numsquares, flick2use, set.alphalevel, set.refreshrate);

	Matrix FLICKSXreal = Flicker.flickrates(f.trial, frames.xreal, mon.numsquares, flick2use, set.alphalevel, set.refreshrate);
	Matrix FLICKSYreal = Flicker.flickrates(f.trial, frames.yreal, mon.numsquares, flick2use, set.alphalevel, set.refreshrate);

	Gradientx.makesquares(mon.height, mon.height, mon.numsquares, mon.xxtra);
	Gradienty.makesquares(mon.height, mon.height, mon.numsquares, mon.xxtra);
	GradientA.makesquares(mon.height, mon.height, mon.numsquares, mon.xxtra);

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
	Freqrange currentfreqrange = Freqrange::real;


	int framecount = 0;
	int Trial = 0;
	int Block = 1;

	sf::RenderWindow window(sf::VideoMode(mon.width, mon.height), "GradientFlicker", sf::Style::None);
	//window.setFramerateLimit(10);
	window.setVerticalSyncEnabled(true);

	std::cout << "Press enter to start" << std::endl;
	bool startgame = false;

	sf::Clock clock;
	std::vector<double> framerate(f.trial);
	while (window.isOpen())
	{

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		framecount++;

		switch (currentsegment) {

		case gamesegments::rest:
			
			if (startgame == false) {
				startgame = gamestarter(startgame, framecount);
				if (startgame == true) {
					framecount = 1;
				}
			};
				
			if (startgame==true) {

				if (framecount == 1) {
					char strN[3];	memset(strN, '\0', sizeof(strN));
					sprintf_s(strN, "%d", Block);
					restscreen.setString(strN);

					trigger(trig.rest);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					std::cout << "Block :" << Block << std::endl;
					switch (flick2use) {
					case flicktype::smooth:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
						break;
					case flicktype::smoothsingle:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						break;
					case flicktype::smoothnoalph:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
						break;

					}

					switch (currentfreqrange) {
					case Freqrange::real:
						std::cout << "Real Frequencies"<< std::endl;
						FLICKSX = FLICKSXreal;
						FLICKSY = FLICKSYreal;
						break;
					case Freqrange::imag:
						std::cout << "Imaginary Frequencies" << std::endl;
						FLICKSX = FLICKSXimag;
						FLICKSY = FLICKSYimag;
						break;
					}


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
				switch (flick2use) {
				case flicktype::smooth:
					switch (currentfreqrange) {
					case Freqrange::real:
						trigger(tilepos[Trial]+1);
						break;
					case Freqrange::imag:
						trigger(tilepos[Trial]+11);
						break;
					}
					break;
				case flicktype::smoothsingle:
					switch (currentfreqrange) {
					case Freqrange::real:
						trigger(tilepos[Trial]+101);
						break;
					case Freqrange::imag:
						trigger(tilepos[Trial] + 111);
						break;
					}
					break;
				case flicktype::smoothnoalph:
					switch (currentfreqrange) {
					case Freqrange::real:
						trigger(tilepos[Trial] + 201);
						break;
					case Freqrange::imag:
						trigger(tilepos[Trial] + 211);
						break;
					}
					break;
				}

				cueshape = cue.rendercuedot(mon.height, mon.height, mon.numsquares, tilepos[Trial], mon.xxtra);
				std::cout << "Trial: " << Trial + 1 << std::endl;
			}

			if (framecount == 6) {
				trigger(trig.null);
			}

			window.clear();

			switch (flick2use) {
			case flicktype::smooth:
				Gradientx.flick(FLICKSX, framecount, mon.numsquares, 1, flick2use); //x
				Gradienty.flick(FLICKSY, framecount, mon.numsquares, 2, flick2use); //y

				window.draw(Gradienty);
				window.draw(Gradientx);

				break;
			case flicktype::smoothsingle:
				Gradientx.flicksingle(FLICKSX, framecount, mon.numsquares, 1, flick2use); //x
				Gradienty.flicksingle(FLICKSY, framecount, mon.numsquares, 2, flick2use); //y

				window.draw(Gradienty);
				window.draw(Gradientx);

				break;
			case flicktype::smoothnoalph:
				GradientA.flicknoalph(FLICKSX, FLICKSY, framecount, mon.numsquares, 1, flick2use); //x

				window.draw(GradientA);

				break;

			}

			window.draw(cueshape);

			
			if (framecount == f.trial - 1) {
				framecount = 0;
				
				if (Trial == mon.numsquares*mon.numsquares-1) {
					
					Trial = -1;

					tilepos = cue.randpos(mon.numsquares);

					switch (flick2use) {
					case flicktype::smooth:
						flick2use = flicktype::smoothsingle;
						break;
					case flicktype::smoothsingle:
						flick2use = flicktype::smoothnoalph;
						break;
					case flicktype::smoothnoalph:
						flick2use = flicktype::smooth;

						switch (currentfreqrange) {
						case Freqrange::real:
							currentfreqrange = Freqrange::imag;
							break;
						case Freqrange::imag:
							currentfreqrange = Freqrange::real;
							break;
						}
						break;

					}

					Block++;

					if (Block > set.nblocks) {
						window.close();
					}

					currentsegment = gamesegments::rest;
					
				}

				/*char* file = "framerateGF.mat";
				char* varname = "framerate";
				int matsave = matcreate(file, framerate, f.trial, varname);
*/
				
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