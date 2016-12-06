#pragma once
#include <SFML/Graphics.hpp>
#include "flicker.h"
#include "settings.h"
#include "particlesystem.h"
#include "sprites.h"
#include "xboxcontrol.h"

// obsticle setup
sf::VertexArray gen_obsticlepos(int numobs) {
	sf::VertexArray obsticlepos(sf::Lines, numobs);
	for (int i = 0; i < 3; ++i)
	{
		obsticlepos[i].position = sf::Vector2f(std::rand() % mon.width + mon.width, std::rand() % 900 + 80);
	}

	return obsticlepos;
}


char* direct_data = "screenshots3\\";
const char* filetype = ".bmp";
char*  file2save = new char[1];
size_t bufsize = 200;


void draw_shit(sf::RenderWindow* window) {

	// controller 

	GamePadXbox* joystick = new GamePadXbox(1);


	// explosion prep
	sf::VertexArray quad1(sf::Lines, 25);
	int tilesize = 64;
	int count = 0;

	for (int j = 0; j < 5; ++j)
		for (int i = 0; i < 5; ++i)
		{
			quad1[count].position = sf::Vector2f(i*tilesize, j*tilesize);
			count = count + 1;
		}



	// check joystickconnection
	if (movetype == control::controller) {
		if (sf::Joystick::isConnected(0))
		{
			std::cout << "joystick connected!" << std::endl;
		}
	}

	// flicker related things
	flicker Flicker;
	Matrix FLICKS = Flicker.flickrates(f.trial, frames.Hzintended, frames.nHz, flick2use, set.alphalevel, mon.ref);

	//sprites!
	sprites create;

	sf::Image CURSOR = create.GetImage("stim\\saucer.png");
	sf::Image BACKGROUND = create.GetImage("stim\\trees.png");
	sf::Image EXPLOSION = create.GetImage("stim\\explosion.png");
	sf::Image BALL = create.GetImage("stim\\ball.png");
	BALL.createMaskFromColor(sf::Color(0, 0, 0));

	sf::Texture cursortext = create.GetTexture(CURSOR);
	sf::Texture backgroundtext = create.GetTexture(BACKGROUND);
	sf::Texture explosiontext = create.GetTexture(EXPLOSION);
	sf::Texture balltext = create.GetTexture(BALL);

	sf::Sprite target1 = create.cursor();
	sf::Sprite target2 = create.cursor();
	sf::Sprite ball = create.cursor();
	sf::Sprite background = create.GetBackground(BACKGROUND);
	sf::Sprite obsticle = create.obsticle();

	target1.setTexture(cursortext);
	target2.setTexture(cursortext);
	background.setTexture(backgroundtext);
	obsticle.setTexture(explosiontext);
	ball.setTexture(balltext);

	int start = 0;
	obsticle.setTextureRect(sf::IntRect(int(quad1[start].position.x), int(quad1[start].position.y), 64, 64));
	int picwidth = BACKGROUND.getSize().x;

	//particles?
	//ParticleSystem particles(3000);

	// target points
	sf::CircleShape shape(50);
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(0, 0, 0));

	sf::VertexArray obsticlepos = gen_obsticlepos(set.numobs);
	sf::VertexArray obsticlepos_green = gen_obsticlepos(set.numobs);
	int xobsticlepos;

	// text

	sf::Font font;
	if (!font.loadFromFile("stim\\impact.ttf"))
	{// error...
	}
	sf::Text score;
	score.setFont(font);
	score.setString("0");
	score.setCharacterSize(100);
	score.setColor(sf::Color::Black);
	score.setPosition(sf::Vector2f(mon.width - 200, 50));

	//timing things
	sf::Clock clock;
	std::vector<double> framerate(f.trial);
	int framecount = 0;
	int Ecount = 0;
	int Ecount_G = 0;
	double flickstate;
	bool firstflip = true;
	float cursorYpos;
	float cursorXpos = mon.xcentre - 300;
	bool explode = false;
	bool explode_green = false;
	int explosioncase;
	int explosioncase_green;
	int points = 0;

	// drawing loop!
	while (window->isOpen())
	{

		window->clear(sf::Color::Black);

		// move background
		set.backgroundshift = set.backgroundshift - set.backgroundshift_rate;
		if (set.backgroundshift < -picwidth) {
			set.backgroundshift = set.backgroundshift + picwidth;
		}

		background.setPosition(sf::Vector2f(set.backgroundshift, 0)); //pic1
		window->draw(background);
		background.setPosition(sf::Vector2f(set.backgroundshift + picwidth, 0)); //pic2
		window->draw(background);

		// get cursor movement
		switch (movetype) {
		case control::server:
			result2use = result; result = 0;
			if (result2use > 128) {
				result2use = -256 + result2use;
			}
			break;
		case control::keyboard:
			result2use = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				result2use = result2use - 5;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				result2use = result2use + 5;
			}
			break;

		case control::controller:
			sf::Joystick::update();
			result2use = sf::Joystick::getAxisPosition(0, sf::Joystick::R);

			
			break;

		}

		set.shift = set.shift + result2use;

		// flicker cursor
		flickstate = FLICKS[0][framecount];
		target1.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate], clut.white[flickstate]));
		flickstate = FLICKS[2][framecount];
		target2.setColor(sf::Color(clut.white[flickstate], clut.white[flickstate], clut.white[flickstate, clut.white[flickstate]]));

		//draw cursor
		cursorYpos = mon.ycentre + set.shift;
		/*if (cursorYpos < 100) { cursorYpos = 101; }
		if (cursorYpos > mon.height) { cursorYpos = mon.height - 1; }*/
		cursorXpos = mon.xcentre - 300;
		target1.setPosition(sf::Vector2f(cursorXpos - set.rawtargetsize / 2 , cursorYpos - set.rawtargetsize / 2));
		target2.setPosition(sf::Vector2f(cursorXpos - set.rawtargetsize / 2, cursorYpos - set.rawtargetsize / 2));

		window->draw(target2);
		window->draw(target1);



		//obsticles
		ball.setColor(sf::Color(255, 0, 0));
		for (int i = 0; i < set.numobs; ++i) {
			// move obsticles
			obsticlepos[i].position.x = obsticlepos[i].position.x - set.backgroundshift_rate;
			if (obsticlepos[i].position.x < -50) {
				obsticlepos[i].position = sf::Vector2f(std::rand() % mon.width + mon.width, std::rand() % 900 + 80);
			}

			ball.setPosition(sf::Vector2f(obsticlepos[i].position.x, obsticlepos[i].position.y)); //
			

			if ((obsticlepos[i].position.x < cursorXpos + 150)  & (obsticlepos[i].position.x > cursorXpos - 150)  & (obsticlepos[i].position.y < cursorYpos + 50) & (obsticlepos[i].position.y > cursorYpos - 250)) {
				explode = true;
				explosioncase = i;
				if (movetype == control::controller) {
					joystick->vibrate(1, 0);
				}
			}
			else {
				window->draw(ball);
			}
		}

		ball.setColor(sf::Color(0, 255, 0));
		for (int i = 0; i < set.numobs; ++i) {
			// move obsticles
			obsticlepos_green[i].position.x = obsticlepos_green[i].position.x - set.backgroundshift_rate;
			if (obsticlepos_green[i].position.x < -50) {
				obsticlepos_green[i].position = sf::Vector2f(std::rand() % mon.width + mon.width, std::rand() % 900 + 80);
			}

			ball.setPosition(sf::Vector2f(obsticlepos_green[i].position.x, obsticlepos_green[i].position.y)); //
			
			if ((obsticlepos_green[i].position.x < cursorXpos + 150)  & (obsticlepos_green[i].position.x > cursorXpos - 150)  & (obsticlepos_green[i].position.y < cursorYpos + 50) & (obsticlepos_green[i].position.y > cursorYpos - 300)) {
				explode_green = true;
				explosioncase_green = i;
			}
			else {
				window->draw(ball);
			}
		}


		if (explode) {
			obsticle.setColor(sf::Color(255,255,255));
			obsticle.setTextureRect(sf::IntRect(int(quad1[Ecount].position.x), int(quad1[Ecount].position.y), tilesize, tilesize));
			obsticle.setPosition(sf::Vector2f(obsticlepos[explosioncase].position.x-100, obsticlepos[explosioncase].position.y - 100));

			window->draw(obsticle);

			Ecount++;
			if (Ecount > 24) {
				Ecount = 0;
				points = points - 10;
			}
		}

		if (explode_green) {
			obsticle.setColor(sf::Color(0, 255, 0));
			obsticle.setTextureRect(sf::IntRect(int(quad1[Ecount_G].position.x), int(quad1[Ecount_G].position.y), tilesize, tilesize));
			obsticle.setPosition(sf::Vector2f(obsticlepos_green[explosioncase_green].position.x - 100, obsticlepos_green[explosioncase_green].position.y - 100));

			window->draw(obsticle);

			Ecount_G++;
			if (Ecount_G > 24) {
				Ecount_G = 0;
				points = points + 1;
			}
		}

		// score
		if (points < 0) {
			score.setColor(sf::Color::Red);
		}
		else {
			score.setColor(sf::Color::Black);
		}
		char str[6]; 	memset(str, '\0', sizeof(str));
		sprintf_s(str, "%d", points);
		score.setString(str);


		window->draw(score);

		// timing things
		sf::Time refresh = clock.restart();
		framerate[framecount] = refresh.asMicroseconds();

		framecount++;
		if (framecount > f.trial - 1) {
			framecount = 1;
			/*if (set.backgroundshift_rate < 15) {
				set.backgroundshift_rate = set.backgroundshift_rate + 1;
			}*/
		}

		if (Ecount == 0) {
			explode = false;
		}

		if (Ecount_G == 0) {
			explode_green = false;
		}
		

		// particles?
		//particles.setEmitter(window->mapPixelToCoords(sf::Vector2i(mon.xcentre - set.rawtargetsize / 2, mon.ycentre + set.shift - set.rawtargetsize / 2)));
		//particles.update(refresh, -10, firstflip);
		//if (firstflip) { firstflip = false; }
		//window->draw(particles);


		//display!
		window->display();
		
		if (set.screenshot) {
		sf::Image screenshot = window->capture();


		char FRAME[6]; 	memset(FRAME, '\0', sizeof(FRAME));
		sprintf_s(FRAME, "%d", framecount);

		
		strcpy_s(file2save, bufsize, direct_data);
		if (framecount < 10) { strcpy_s(file2save, bufsize, "000"); }
		else if (framecount < 100) { strcpy_s(file2save, bufsize, "00"); }
		else if (framecount < 1000) { strcpy_s(file2save, bufsize, "0"); }
		strcat_s(file2save, bufsize, FRAME);
		strcat_s(file2save, bufsize, filetype);

		screenshot.saveToFile(file2save);
		}

	}
}