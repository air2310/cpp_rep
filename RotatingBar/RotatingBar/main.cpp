#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma once

#include <SFML/Graphics.hpp>
#include "drawshit.h"
#include "settings.h"

int main() {

	// open window
	sf::RenderWindow window(sf::VideoMode(mon.width, mon.height), "some moving stuff", sf::Style::None);
	window.setPosition(sf::Vector2i(1920, 0));
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
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}


	return 0;
}

