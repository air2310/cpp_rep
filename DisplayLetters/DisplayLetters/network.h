#pragma once
#include <SFML/Network.hpp>
#include "settings.h"
#include <iostream>

const unsigned short PORT = 1972;
const std::string IPADDRESS("10.16.97.13");

sf::TcpSocket client;
sf::Mutex globalMutex;


void Server(void)
{
	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(client);

	std::cout << "New client connected: " << client.getRemoteAddress() << std::endl;
}


void get_data(void) {

	std::size_t received;
	while (true) {

		// TCP socket:
		int data[2];
		data[0] = 0;
		data[1] = 0;

		if (client.receive(data, 10, received) != sf::Socket::Done)
		{// error...
		}

		globalMutex.lock();
		result = data[0];
		globalMutex.unlock();

		std::cout << data[0] << std::endl;
		std::cout << data[1] << std::endl;

	}

}