#include <SFML/Graphics.hpp>
# include "Header.h"
#include <iostream>


#include <windows.h>
#include <tchar.h>


#include <chrono>

int ftrial = 1200;

int framecount = 0;
int R;
double pi = 3.1415926535;
int a = 255/2;
double refreshrate = 60;
double Hz = 8;
double frames = refreshrate / Hz;
float x;
sf::Time refresh;
sf::Time elapsed;
float Lum;

char* file;
char* varname;


//start = std::chrono::high_resolution_clock::now();
//...
//auto elapsed = std::chrono::high_resolution_clock::now() - start;
//
//long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
//


int main() {
	
	DWORD dwError, dwThreadPri;


	if (!SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS))
	{
		dwError = GetLastError();
		if (ERROR_PROCESS_MODE_ALREADY_BACKGROUND == dwError)
			_tprintf(TEXT("Already in background mode\n"));
		else _tprintf(TEXT("Failed to enter background mode (%d)\n"), dwError);
	}


	if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL)) //THREAD_MODE_BACKGROUND_BEGIN //
	{
		dwError = GetLastError();
		if (ERROR_THREAD_MODE_ALREADY_BACKGROUND == dwError)
			_tprintf(TEXT("Already in background mode\n"));
		else _tprintf(TEXT("Failed to enter background mode (%d)\n"), dwError);

		int a;
		std::cin >> a;

	}

	// Display thread priority

	dwThreadPri = GetThreadPriority(GetCurrentThread());

	_tprintf(TEXT("Current thread priority is 0x%x\n"), dwThreadPri);


	sf::RenderWindow window(sf::VideoMode(1920, 1080), "test", sf::Style::Fullscreen);
	window.setPosition(sf::Vector2i(1920, 0));
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	//window.requestFocus();
	sf::Clock clock1;
	auto start = std::chrono::high_resolution_clock::now();




	sf::RectangleShape shape(sf::Vector2f(1920,1080));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(sf::Vector2f(0, 0));


	std::vector<double> framerate(ftrial);
	std::vector<double> luminance(ftrial);

	Lum = 255;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		elapsed = clock1.getElapsedTime();
		//auto elapsed = std::chrono::high_resolution_clock::now() - start;
		//long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();


		//x = double(microseconds) / 1000000;
		x = elapsed.asSeconds();
		Lum = a*sin(2 * pi * Hz*x - pi) + a;
		
		std::cout << Lum << std::endl;

		shape.setFillColor(sf::Color(Lum, Lum, Lum));
		window.draw(shape);
		window.display();


		framerate[framecount] = x;
		luminance[framecount] = Lum;

		framecount++;
		if (framecount > ftrial - 1) {
			file = "Latency_TC3.mat";
			varname = "latency";
			matcreate(file, framerate, ftrial, varname);

			file = "luminance.mat";
			varname = "lum";
			matcreate(file, luminance, ftrial, varname);

			window.close();
			framecount = 1;
		}

	}


	if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL)) //THREAD_MODE_BACKGROUND_END
	{
		_tprintf(TEXT("Failed to end background mode (%d)\n"), GetLastError());
	}

	if (!SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS))
	{
		_tprintf(TEXT("Failed to end background mode (%d)\n"), GetLastError());
	}


	return 0;
}