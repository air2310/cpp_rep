#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct screen {
	int width = 1920;
	int height = 1080;

	int xcentre = width / 2;
	int ycentre = height / 2;

	int ref = 60;

}; screen mon;

sf::Image GetImage(const char* imagelocation) {
	sf::Image TARGET;
	TARGET.loadFromFile(imagelocation);

	return TARGET;
}

sf::Texture GetTexture(sf::Image IMAGE) {
	sf::Texture texture;
	if (!texture.loadFromImage(IMAGE)) {
		std::cout << "error loading an image" << std::endl;
	}

	return texture;
}




int main() {

	// stripes prep
	sf::VertexArray quad1(sf::Lines, 28);
	int tilesize = 137;
	int count = 0;


	for (int i = 0; i < 14; ++i)
		for (int j = 0; j < 2; j++) {
			quad1[count].position = sf::Vector2f(i*tilesize, 0);
			count = count + 1;
		}


	// open window
	sf::RenderWindow window(sf::VideoMode(mon.width, mon.height), "some moving stuff", sf::Style::None);
	window.setPosition(sf::Vector2i(mon.width, 0));
	window.setVerticalSyncEnabled(true);

	sf::Image ROAD = GetImage("stim\\road.png");
	sf::Image STRIPES = GetImage("stim\\stripes.png");
	sf::Image DESERT = GetImage("stim\\sand1.png");
	sf::Image DESERT2 = GetImage("stim\\sand2.png");
	sf::Image DESERT3 = GetImage("stim\\sand3.png");
	sf::Image CACTI = GetImage("stim\\cactus.png");
	//CACTI.createMaskFromColor(sf::Color(255, 255, 255));

	sf::Texture road_text = GetTexture(ROAD);
	sf::Texture stripes_text = GetTexture(STRIPES);
	sf::Texture desert_text = GetTexture(DESERT);
	sf::Texture desert_text2 = GetTexture(DESERT2);
	sf::Texture desert_text3 = GetTexture(DESERT3);
	sf::Texture cactus_text = GetTexture(CACTI);

	sf::Sprite road;
	road.setTexture(road_text);

	sf::Vector2u roadsize = ROAD.getSize();
	float xscale = float(mon.width) / float(roadsize.x);
	road.setScale(sf::Vector2f(xscale, xscale)); //
	road.setPosition(sf::Vector2f(0, mon.height - roadsize.y*xscale));

	sf::Sprite stripes;
	stripes.setTexture(stripes_text);
	stripes.setTextureRect(sf::IntRect(int(quad1[0].position.x), int(quad1[0].position.y), tilesize, 1241));
	stripes.setScale(sf::Vector2f(0.56, xscale));
	stripes.setPosition(sf::Vector2f(mon.width / 2 - tilesize*0.56 / 2, mon.height - roadsize.y*xscale));

	sf::Sprite background;
	background.setTexture(desert_text);

	sf::Vector2u backsize = DESERT.getSize();
	sf::Vector2f scale = sf::Vector2f(float(mon.width) / float(backsize.x), float(mon.height) / float(backsize.y));
	background.setScale(sf::Vector2f(scale.x, scale.y));
	background.setPosition(sf::Vector2f(0, 0));

	sf::Sprite background2;
	background2.setTexture(desert_text2);
	background2.setScale(sf::Vector2f(scale.x, scale.y));
	background2.setPosition(sf::Vector2f(0, 0));

	sf::Sprite background3;
	background3.setTexture(desert_text3);
	background3.setScale(sf::Vector2f(scale.x, scale.y));
	background3.setPosition(sf::Vector2f(0, 0));
	

	sf::Sprite cactus;
	cactus.setTexture(cactus_text);
	cactus.setOrigin(sf::Vector2f(123, 234));
	cactus.setScale(sf::Vector2f(0.02, 0.02));
	cactus.setPosition(sf::Vector2f(mon.width / 2 - tilesize*0.56 / 2 - 30, 430));

	sf::Sprite cactus2;
	cactus2.setTexture(cactus_text);
	cactus2.setOrigin(sf::Vector2f(123, 234));
	cactus2.setScale(sf::Vector2f(0.02, 0.02));
	cactus2.setPosition(sf::Vector2f(100+mon.width / 2 - tilesize*0.56 / 2 , 440));

	int sandtype = 1;
	int sand_count = 0;
	int stripe_count = count - 1;
	sf::Vector2f accelerate = sf::Vector2f(0.125f / 10, 0.00125f / 10);
	sf::Vector2f accelerate2 = sf::Vector2f(0.0125f / 10, 0.00125f / 10);
	sf::Vector2f moverate = sf::Vector2f(0.125f/10, 0.00125f/10);
	sf::Vector2f moverate2 = sf::Vector2f(0.125f, 0.00125f);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(0, 0, 0));


		switch (sandtype) {
		case 1:
			window.draw(background);
			break;
		case 2:
			window.draw(background2);
			break;
		case 3:
			window.draw(background3);
			break;
	}

	//window.draw(background);
	//window.draw(road);


	stripes.setTextureRect(sf::IntRect(int(quad1[stripe_count].position.x), int(quad1[stripe_count].position.y), tilesize, 1241));
	window.draw(stripes);

	accelerate = sf::Vector2f(accelerate.x+ 0.0003, accelerate.y +0.0001);
	moverate = sf::Vector2f(moverate.x-accelerate.x, moverate.y + accelerate.y);
	if (cactus.getPosition().x < 0) {
		cactus.setScale(sf::Vector2f(0.02, 0.02));
		cactus.setPosition(sf::Vector2f(mon.width / 2 - tilesize*0.56 / 2-30, 430));
		moverate = sf::Vector2f(0.125f, 0.00125f);
		accelerate = sf::Vector2f(0.125f / 10, 0.00125f / 10);
	}
	cactus.move(sf::Vector2f(moverate.x,moverate.y)); 
	cactus.scale(sf::Vector2f(1.016f, 1.016f));
	window.draw(cactus);

	accelerate2 = sf::Vector2f(accelerate.x + 0.00001, accelerate.y + 0.00001);
	moverate2 = sf::Vector2f(moverate2.x + accelerate2.x, moverate2.y + accelerate2.y);
	if (cactus2.getPosition().x > mon.width) {
		cactus2.setScale(sf::Vector2f(0.02, 0.02));
		cactus2.setPosition(sf::Vector2f(100 + mon.width / 2 - tilesize*0.56 / 2, 440));
		moverate2 = sf::Vector2f(0.00125f, 0.000125f);
		accelerate2 = sf::Vector2f(0.0125f / 10, 0.00125f / 10);
	}
	cactus2.move(sf::Vector2f(moverate2.x, moverate2.y));
	cactus2.scale(sf::Vector2f(1.016f, 1.016f));


	window.draw(cactus2);

	window.display();

	stripe_count--;
	if (stripe_count < 0) {
		stripe_count = count - 1;

	}

	sand_count++;
	if (sand_count > 5) {

		sand_count = 0;

		switch (sandtype) {
		case 1:
			sandtype = 2;
			break;
		case 2:
			sandtype = 3;
			break;
		case 3:
			sandtype = 1;
			break;
		}
	}

}
	return 0;
}