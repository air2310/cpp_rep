//#pragma comment(lib, "sfml-network.lib")

#include <iostream>
#include <SFML/Network.hpp>

//#include <SFML/Graphics.hpp>

const unsigned short PORT = 1974;
const std::string IPADDRESS("10.16.97.13");//change to suit your needs

//std::string msgSend;
//sf::Int8    msgSend;

sf::TcpSocket client;
sf::Mutex globalMutex;
bool quit = false;


void Server(void)
{
	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(client);

	std::cout << "New client connected: " << client.getRemoteAddress() << std::endl;
}

bool Client(void)
{
	if (client.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected\n";
		return true;
	}
	return false;
}

void get_data(void){

	std::size_t received;
	while (true) {

		// TCP socket:
		//char data[17];
		int data[1];

		data[0] = 0;

		if (client.receive(data, 10, received) != sf::Socket::Done)
		{
			// error...
		}
		std::cout << "Received " << received << " bytes" << std::endl;
		std::cout << data[0] << std::endl;

	}

}


int main() {
	std::cout << "opening server" << std::endl;
	Server();
	std::cout << "done with that" << std::endl;
	//Client();

	sf::Thread* thread = 0;
	thread = new sf::Thread(&get_data);
	thread->launch();

	if (thread)
	{
		thread->wait();
		delete thread;
	}

	
	//sf::Uint8 data;


	//std::size_t received;
	//while (true) {
	//	
	//	// TCP socket:
	//	//char data[17];
	//	int data[1];

	//	data[0] = 0;

	//	if (client.receive(data, 10, received) != sf::Socket::Done)
	//	{
	//		// error...
	//	}
	//	std::cout << "Received " << received << " bytes" << std::endl;
	//	std::cout << data[0] << std::endl;

	//}





		int pause;
		std::cin >> pause;


		return 0;
}











//void DoStuff(void)
//{
//	static std::string oldMsg;
//	while (!quit)
//	{
//		sf::Packet packetSend;
//		globalMutex.lock();
//		packetSend << msgSend;
//		globalMutex.unlock();
//
//		socket.send(packetSend);
//
//		//std::string msg;
//		sf::Int8 msg;
//		sf::Packet packetReceive;
//
//		socket.receive(packetReceive);
//		packetReceive >> msg;
//		/*if (packetReceive >> msg)
//		{
//			if (oldMsg != msg)
//				if (!msg.empty())
//				{*/
//					std::cout << msg << std::endl;
//					/*oldMsg = msg;
//				}
//		}*/
//	}
//}
//void Server(void)
//{
//	sf::TcpListener listener;
//	listener.listen(PORT);
//	listener.accept(socket);
//	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
//}
//bool Client(void)
//{
//	if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
//	{
//		std::cout << "Connected\n";
//		return true;
//	}
//	return false;
//}
//void GetInput(void)
//{
//	std::string s;
//	sf::Int8    x;
//
//	std::cin >> x;
//	if (s == "exit")
//	quit = true;
//	globalMutex.lock();
//	msgSend = x;
//	globalMutex.unlock();
//}
//int main(int argc, char* argv[])
//{
//	sf::Thread* thread = 0;
//
//	char who;
//	std::cout << "Do you want to be a server (s) or a client (c) ? ";
//	std::cin >> who;
//
//	if (who == 's')
//		Server();
//	else
//		Client();
//
//	thread = new sf::Thread(&DoStuff);
//	thread->launch();
//
//	std::cout << "\nEnter \"exit\" to quit or message to send: ";
//	while (!quit)
//	{
//		GetInput();
//	}
//	if (thread)
//	{
//		thread->wait();
//		delete thread;
//	}
//	return 0;
//}

