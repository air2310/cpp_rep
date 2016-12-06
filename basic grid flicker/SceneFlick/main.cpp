#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")

#include "settings.h"
#include "gradient.h"

#include <iostream>;

#include <chrono>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

double x;


int main() {

	// settings
	settings set;

	//setup tiles

	gradient Gradient;

	Gradient.makesquares(set.mon.size.width, set.mon.size.height, set.genset.numSquares.x, set.genset.numSquares.y);


	//setup window
	sf::RenderWindow window(sf::VideoMode(set.mon.size), "some flickering stuff", sf::Style::Fullscreen);
	window.setPosition(sf::Vector2i(-1920, 0));
	window.setVerticalSyncEnabled(true);

	auto start = std::chrono::high_resolution_clock::now();

	int FF = 0;
	while (window.isOpen())
	{
		//process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		
		//clear
		window.clear(sf::Color::Black);

		//flicker
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		double x = double(microseconds) / 1000000;

		
		Gradient.flick(FF, set.genset.numSquares.x, set.genset.numSquares.y, x);

		window.draw(Gradient);

		//display
		window.display();
		FF++;
	}

	return 0;
}