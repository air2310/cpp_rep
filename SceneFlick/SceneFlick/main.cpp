#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")

#include "settings.h"
#include "gradient.h"
#include "writetxt.h"

#include <iostream>;

#include <chrono>

#include <windows.h>
#include <tchar.h>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

double x;


int main() {

	DWORD dwError, dwThreadPri;


	if (!SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS))
	{
		dwError = GetLastError();
		_tprintf(TEXT("Failed to enter realtime priority (%d)\n"), dwError);
	}


	if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL)) //THREAD_MODE_BACKGROUND_BEGIN //
	{
		dwError = GetLastError();

		_tprintf(TEXT("Failed to enter timecritical priority (%d)\n"), dwError);

		int a;
		std::cin >> a;

	}

	// Display thread priority

	dwThreadPri = GetThreadPriority(GetCurrentThread());
	_tprintf(TEXT("Current thread priority is 0x%x\n"), dwThreadPri);

	// settings
	settings set;

	//setup beach

	sf::Texture texture;
	if (!texture.loadFromFile("beach.jpg"))	{		// error...
	}
	sf::Sprite beach;
	beach.setTexture(texture);
	beach.setScale(sf::Vector2f(1.2f, 0.9f));

	//setup tiles
	gradient Gradient;
	Gradient.makesquares(set.mon.size.width, set.mon.size.height, set.genset.numSquares.x, set.genset.numSquares.y);


	//setup window
	sf::RenderWindow window(sf::VideoMode(set.mon.size), "some flickering stuff", sf::Style::Fullscreen);
	//window.setPosition(sf::Vector2i(1920, 0));
	window.setVerticalSyncEnabled(true);

	inittxt();

	auto start = std::chrono::high_resolution_clock::now();
	int FF = 0;
	std::vector<float> framerate(set.timing.frames+1);

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
		framerate[FF] = x;
		
		Gradient.flick(FF, set.genset.numSquares.x, set.genset.numSquares.y, x);

		//draw

		window.draw(beach);
		window.draw(Gradient);

		//display
		window.display();
		FF++;

		if (FF > set.timing.frames) {
			writetxt(FF, framerate, set.timing.frames);

			window.close();
		}
	}



	if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL)) //THREAD_MODE_BACKGROUND_END
	{
		_tprintf(TEXT("Failed to end time critical priority (%d)\n"), GetLastError());
	}

	if (!SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS))
	{
		_tprintf(TEXT("Failed to end realtime mode (%d)\n"), GetLastError());
	}

	return 0;
}