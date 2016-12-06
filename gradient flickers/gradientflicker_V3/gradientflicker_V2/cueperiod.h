#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>   // randon shuffle
#include <ctime>  //std::time

int myrandom(int i) { return std::rand() % i; }

class cueperiod {
public:
	sf::RectangleShape rendercue(int width, int height, int numsquares, int Trial) {

		std::vector<sf::Vector2f> tileposition = tilepos(numsquares); 
		int i = tileposition[Trial].x;
		int j = tileposition[Trial].y;
		sf::Vector2f tileSize = { float(width / numsquares), float(height / numsquares) };
		sf::Vector2f tileSizedraw = { float(width / numsquares)-20, float(height / numsquares)-20 };

		sf::Vector2f cueloc = sf::Vector2f(i * tileSize.x + 10, j * tileSize.y + 10);

		sf::RectangleShape cueshape(tileSizedraw);
		cueshape.setOutlineThickness(10);
		cueshape.setOutlineColor(sf::Color(0, 0, 255, 255));
		cueshape.setFillColor(sf::Color(0, 0, 0, 0));
		cueshape.setPosition(cueloc);
		return cueshape;
	}

	std::vector<double> randpos(int numsquares) {
		std::vector<double> randpos(numsquares*numsquares);
		for (int i = 0; i < numsquares*numsquares; ++i) {
			randpos[i] = i;
		}
		std::srand(unsigned(std::time(0))); //randomiser
		std::random_shuffle(randpos.begin(), randpos.end(), myrandom); //randomly shuffle elements
		return randpos;
	}

private:
	std::vector<sf::Vector2f> tilepos(int numsquares) {
		std::vector<sf::Vector2f> tilepos(numsquares*numsquares);
		sf::Vector2f T;

		int count = 0;
		for (int i = 0; i < numsquares; ++i)
			for (int j = 0; j < numsquares; ++j) {
				T.x = float(i);
				T.y = float(j);
				tilepos[count] = T;
				count++;
			}
		
		return tilepos;
	};

};
