#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "xboxcontrol.h"
#include <iostream>


class settings {
public:
	int width = 1920;
	int height = 1080;
	int ref = 144;
};
settings mon;

int playtime = 60;
int flicktime = playtime*mon.ref;

std::vector<double> createtcol(int flicktime) {
	std::vector<double> tcol(flicktime);
	std::srand(unsigned(std::time(0))); //randomiser

	for (int A = 0; A <flicktime; A++) {
		tcol[A] = rand() % 255 + 1;
	}

	return tcol;
}
std::vector<double> tcol = createtcol(flicktime);


void renderingThread(sf::RenderWindow* window, int frame,std::vector<double> framerate, sf::CircleShape xbox, sf::CircleShape target, GamePadXbox* Player1, GamePadXbox* Player2)
{
	// the rendering loop
	
		XINPUT_STATE _controllerState1 = Player1->GetState();
		XINPUT_STATE _controllerState2 = Player2->GetState();

		float RightThumbY1 = _controllerState1.Gamepad.sThumbRY;
		float RightThumbX1 = _controllerState1.Gamepad.sThumbRX; // x= 1885 y = 586

		float RightThumbY2 = _controllerState2.Gamepad.sThumbRY;
		float RightThumbX2 = _controllerState2.Gamepad.sThumbRX; // x= 1885 y = 586

	    std::cout << RightThumbX1 << "  " << RightThumbY1 << "  " << RightThumbX2 << "  " << RightThumbY2 << std::endl;

		float xpos1 = (RightThumbX1 / 32768)*mon.width + mon.width / 2;
		float ypos1 = -(RightThumbY1 / 32768)*mon.height + mon.height / 2;

		float xpos2 = (RightThumbX2 / 32768)*mon.width + mon.width / 2;
		float ypos2 = -(RightThumbY2 / 32768)*mon.height + mon.height / 2;


		window->clear(sf::Color::Black);

		target.setFillColor(sf::Color(tcol[frame], tcol[frame], tcol[frame]));

		target.setPosition(sf::Vector2f(mon.width / 4, mon.height / 4));
		window->draw(target);
		target.setPosition(sf::Vector2f(3 * mon.width / 4, mon.height / 4));
		window->draw(target);
		target.setPosition(sf::Vector2f(mon.width / 4, 3 * mon.height / 4));
		window->draw(target);
		target.setPosition(sf::Vector2f(3 * mon.width / 4, 3 * mon.height / 4));
		window->draw(target);

		xbox.setPosition(sf::Vector2f(xpos1, ypos1)); // absolute position
		window->draw(xbox);
		xbox.setPosition(sf::Vector2f(xpos2, ypos2)); // absolute position
		window->draw(xbox);

		// display the current frame
		window->display();

	
}


int main()
{

	GamePadXbox* Player1 = new GamePadXbox(1);
	GamePadXbox* Player2 = new GamePadXbox(2);

	// create the window
	sf::RenderWindow window(sf::VideoMode(mon.width, mon.height), "crazy flicker", sf::Style::None);
	window.setVerticalSyncEnabled(true);


	sf::CircleShape xbox(10);
	xbox.setFillColor(sf::Color(0, 255, 0));

	sf::CircleShape target(20);


	sf::Clock clock;
	int frame = 0;
	std::vector<double> framerate(flicktime);

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		frame = ++frame;

		if (frame < flicktime) {
			renderingThread(&window, frame, framerate, xbox, target, Player1, Player2);

			sf::Time refresh = clock.restart();
			framerate[frame] = refresh.asMicroseconds();

		}
		else if (frame == flicktime - 1) {

			char* file = "frameratexbox.mat";
			char* varname = "framerate";
			int matsave = matcreate(file, framerate, flicktime, varname);

			event.type = sf::Event::Closed;
		}
	}


	delete Player1;
	return 0;
}