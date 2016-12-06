#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma once

#include <SFML/Graphics.hpp>
#include "drawshit.h"
#include <iostream>;
#include "writetxt.h";

// 24 blocks of 40 trials
int main() {

	//random seed
	std::srand(std::time(0));

	// open window
	sf::RenderWindow window(sf::VideoMode(mon.size), "some moving stuff", sf::Style::Fullscreen);
	window.setPosition(sf::Vector2i(-1920, 0));
	window.setVerticalSyncEnabled(true);
	window.setActive(false);


	//open drawthread
	sf::Thread* drawthread = 0;
	drawthread = new sf::Thread(&draw_shit, &window);
	drawthread->launch();

	//continue running the threads
	if (drawthread)
	{
		drawthread->wait();
		delete drawthread;
	}

	// handle events
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}

	return 0;
}

