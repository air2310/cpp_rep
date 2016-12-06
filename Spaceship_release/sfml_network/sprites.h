#pragma once

#include "drawshit.h"
class sprites {
public:

	// ----- sprites 1! -----

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

	sf::Sprite cursor() {

		sf::Sprite cursor;

		cursor.setScale(sf::Vector2f(set.targetsize, set.targetsize));
		cursor.setPosition(sf::Vector2f(mon.xcentre - set.rawtargetsize / 2, mon.ycentre - set.rawtargetsize / 2));

		return cursor;
	}

	sf::Sprite obsticle() {

		sf::Sprite obsticle;
		obsticle.setScale(sf::Vector2f(5, 5));
		return obsticle;
	}


	sf::Sprite GetBackground(sf::Image IMAGE) {
		
		sf::Sprite background;

		sf::Vector2u backsize = IMAGE.getSize();

		float xscale = float(mon.width) / float(backsize.x);
		if (xscale > 1) {
			background.setScale(sf::Vector2f(xscale, xscale)); //
		}

		float yscale = float(mon.height) / float(backsize.y);
		background.setScale(sf::Vector2f(1, yscale)); //

		return background;
	};
};