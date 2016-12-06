#pragma once
//#include "drawshit.h"
//
//// ----- sprites 1! -----
//
//sf::Sprite firsttarget() {
//	
//	sf::Image TARGET;
//	/*TARGET.loadFromFile("stim\\target1.bmp");*/
//	//TARGET.createMaskFromColor(sf::Color(0, 0, 0));
//	TARGET.loadFromFile("stim\\saucer.png");
//
//	sf::Texture TARGET1;
//	if (!TARGET1.loadFromImage(TARGET)) {
//		std::cout << "error loading target 1" << std::endl;
//	}
//
//	sf::Sprite target1;
//	target1.setTexture(TARGET1);
//	target1.setScale(sf::Vector2f(set.targetsize, set.targetsize));
//	target1.setPosition(sf::Vector2f(mon.xcentre - set.rawtargetsize / 2, mon.ycentre - set.rawtargetsize / 2));
//
//	return target1;
//}
//
//sf::Sprite secondtarget() {
//	// ----- sprites 2! -----
//	sf::Image TARGETb;
//	/*TARGETb.loadFromFile("stim\\target2.bmp");
//	TARGETb.createMaskFromColor(sf::Color(0, 0, 0));*/
//	TARGETb.loadFromFile("stim\\saucer.png");
//
//	sf::Texture TARGET2;
//	if (!TARGET2.loadFromImage(TARGETb)) {
//		std::cout << "error loading target 2" << std::endl;
//	}
//	sf::Sprite target2;
//	target2.setTexture(TARGET2);
//	target2.setScale(sf::Vector2f(set.targetsize, set.targetsize));
//	target2.setPosition(sf::Vector2f(mon.xcentre - set.rawtargetsize / 2, mon.ycentre - set.rawtargetsize / 2));
//
//	return target2;
//}
//
//// ----- Background! -----
//
//sf::Image BACKGROUNDimget() {
//	sf::Image BACKGROUND;
//	BACKGROUND.loadFromFile("stim\\trees.png");
//
//	return BACKGROUND;
//}
//
//sf::Sprite Background() {
//	sf::Image BACKGROUND = BACKGROUNDimget();
//
//	sf::Texture background1;
//	if (!background1.loadFromImage(BACKGROUND)) {
//		std::cout << "error loading background" << std::endl;
//	}
//	sf::Sprite background;
//	background.setTexture(background1);
//
//	sf::Vector2u backsize = BACKGROUND.getSize();
//	int picwidth = backsize.x;
//
//	float xscale = float(mon.width) / float(backsize.x);
//	if (xscale > 1) {
//		background.setScale(sf::Vector2f(xscale, xscale)); //
//	}
//
//	float yscale = float(mon.height) / float(backsize.y);
//	background.setScale(sf::Vector2f(1, yscale)); //
//
//	return background;
//};