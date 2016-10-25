#pragma once
#include "settings.h"
#include "triggers.h"
#include <iostream>

sf::Clock clock1;
sf::Clock clock2;
sf::Time elapsed;
sf::Time refresh;

float x;
sf::Uint8 Lum;
int myrandom(int i) { return std::rand() % i; }

std::vector<double> create_cues(const size_t N) { // Which Line Orientation is cued
	std::vector<double> cues(N);
	for (size_t i = 0; i < N; i++) {
		if (i < N / 3) {	
			cues[i] = 0;		}

		else if ((i >((N / 3) - 1)) && (i < (N / 3) * 2)) {
			cues[i] = 1;		}

		else if ((i >((N / 3) - 1) * 2) && (i < N)) {
			cues[i] = 2;		}

	}

	std::srand(unsigned(std::time(0))); //randomiser
	std::random_shuffle(cues.begin(), cues.end(), myrandom); //randomly shuffle elements
	return cues;
}

std::vector<double> cues = create_cues(set.numtrials);


void rotate_bar(sf::RenderWindow* window, sf::CircleShape circle, sf::RectangleShape bar, sf::Time elapsed) {


		//flicker disc
		x = elapsed.asSeconds();
		Lum = f.alphavar*sin(2 * pi * f.Hz*x - pi) + f.alphavar;
		circle.setFillColor(sf::Color(Lum, Lum, Lum));

		//rotate bar
		float Angle = set.BarRotAng*(elapsed.asSeconds() - timing.sum_cue);
		bar.setRotation(Angle);

		//display
		window->draw(circle);
		window->draw(bar);

}

void draw_shit(sf::RenderWindow* window) {

	sf::CircleShape circle(set.patchsize);
	circle.setFillColor(sf::Color(128, 128, 128, 255));
	circle.setOrigin(sf::Vector2f(set.patchcentre, set.patchcentre));
	circle.setPosition(sf::Vector2f(mon.xcentre, mon.ycentre));

	sf::RectangleShape bar = sf::RectangleShape(sf::Vector2f(set.barwidth, set.barheight));
	bar.setFillColor(sf::Color(0, 255, 0));
	bar.setOrigin(set.barcentre);
	bar.setPosition(sf::Vector2f(mon.xcentre, mon.ycentre));

	sf::Font font;
	if (!font.loadFromFile("stim\\impact.ttf"))	{// error...
	}
	sf::Text trial;
	trial.setFont(font);
	trial.setCharacterSize(set.fontsize);
	trial.setColor(sf::Color::White);
	trial.setOrigin(set.fontcentre);
	trial.setPosition(sf::Vector2f(mon.xcentre, mon.ycentre));

	
	std::vector<sf::Int64> framerate(f.trial);
	int framecount = 0;
	int trialcount = 0; std::cout << "Trial: " << trialcount + 1 << std::endl;
	float cuedangle = set.angles2cue[cues[trialcount]];
	if (set.triggers) {	trigger(0);	}

	while (window->isOpen())
	{
		window->clear(sf::Color::Black);
		

		//setup timing
		refresh = clock1.restart();
		elapsed = clock2.getElapsedTime();

		//Draw Trial Number
		if (elapsed.asSeconds() < timing.sum_trialnum) {
			if (set.triggers) {
				if (elapsed.asMilliseconds() < timing.sum_trialnum*1000+500) {
					trigger(set.triggeroptions[7]);
				}
				else if (elapsed.asMilliseconds() < timing.sum_trialnum * 1000 + 1000) {
					trigger(0);
				}
			}

			char str[6]; 	memset(str, '\0', sizeof(str));
			sprintf_s(str, "%d", trialcount+1);
			trial.setString(str);
			window->draw(trial);
		}

		//Draw Cue
		else if (elapsed.asSeconds() < timing.sum_cue) {
			if (set.triggers) {
				if (elapsed.asMilliseconds() < timing.sum_cue * 1000 + 500) {
					trigger(set.triggeroptions[8]);
				}
				else if (elapsed.asMilliseconds() < timing.sum_cue * 1000 + 1000) {
					trigger(0);
				}
			}
			//present cue
			bar.setFillColor(sf::Color(0, 255, 0));
			bar.rotate(cuedangle);
			window->draw(circle);
			window->draw(bar);
			bar.rotate(-cuedangle);
		}

		// Rotating Bar
		else if (elapsed.asSeconds() < timing.sum_BarRot) {

			if (set.triggers) {
				if (elapsed.asMilliseconds() < timing.sum_cue * 1000 + 500) {
					trigger(set.triggeroptions[cues[trialcount]]);
				}
				else if (elapsed.asMilliseconds() < timing.sum_cue * 1000 + 1000) {
					trigger(0);
				}
			}

			bar.setFillColor(sf::Color(0, 255, 0));
			rotate_bar(window, circle, bar, elapsed);

		}

		//Draw Cue again 
		else if (elapsed.asSeconds() < timing.sum_cue2) {
			if (set.triggers) {
				if (elapsed.asMilliseconds() < timing.sum_cue2 * 1000 + 500) {
					trigger(set.triggeroptions[9]);
				}
				else if (elapsed.asMilliseconds() < timing.sum_cue * 1000 + 1000) {
					trigger(0);
				}
			}
			//present cue
			bar.rotate(cuedangle);
			bar.setFillColor(sf::Color(0, 255, 0));
			window->draw(circle);
			window->draw(bar);
			bar.rotate(-cuedangle);

		}

		// Rotating Bar transparent
		else if (elapsed.asSeconds() < timing.sum_BarRot2) {

			if (set.triggers) {
				if (elapsed.asMilliseconds() < timing.sum_BarRot2 * 1000 + 500) {
					trigger(set.triggeroptions[cues[trialcount]]+3);
				}
				else if (elapsed.asMilliseconds() < timing.sum_BarRot2 * 1000 + 1000) {
					trigger(0);
				}
			}

			bar.setFillColor(sf::Color::Transparent);

			rotate_bar(window, circle, bar, elapsed);

		}

		//New Trial
		else if (elapsed.asSeconds() > timing.sum_BarRot2) {
			clock2.restart();
			trialcount++;
			std::cout << "Trial: " << trialcount +1 << std::endl;
			if (trialcount > set.numtrials) {
				window->close();
			}
			cuedangle = set.angles2cue[cues[trialcount]];
		}

		window->display();
	}
	
}

//record
/*framerate[framecount] = refresh.asMicroseconds();
framecount++;
if (framecount > f.trial - 1) {
framecount = 1;
}*/