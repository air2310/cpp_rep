//#pragma comment(lib, "sfml-network.lib")
#pragma once
#include "stdafx.h"


int main() {

	//open server
	if (movetype == control::server) {
		Server();
	}

	// open window
	sf::RenderWindow window(sf::VideoMode(mon.width, mon.height), "some moving stuff", sf::Style::None);
	window.setPosition(sf::Vector2i(-1920, 0));
	window.setVerticalSyncEnabled(true);
	window.setActive(false);

	//open drawthread
	sf::Thread* drawthread = 0;
	drawthread = new sf::Thread(&draw_shit, &window);
	drawthread->launch();



	// start getting data from network 
	if (movetype == control::server) {
		sf::Thread* thread = 0;
		thread = new sf::Thread(&get_data);
		thread->launch();

		if (thread)
		{
			thread->wait();
			delete thread;
		}
	}

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

