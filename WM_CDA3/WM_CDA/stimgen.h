#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <iostream>


class stimgen {
public:
	stimgen();

	std::vector<std::vector<sf::Vector2f>> create_coordinates_all(std::vector<int> trialtype_all);
	std::vector<std::vector<int>> create_colour_order(std::vector<int> trialtype);

	std::vector<sf::RectangleShape> makeboxes(std::vector<std::vector<sf::Vector2f>> coords, std::vector<std::vector<int>> all_colours);
	std::vector<sf::RectangleShape> makefixedboxes(float offset);
	std::vector<sf::RectangleShape> shuffleboxes(std::vector<sf::RectangleShape> boxes, std::vector<std::vector<sf::Vector2f>> coords, int trialnum, std::vector<std::vector<int>> all_colours);
	std::vector<sf::RectangleShape> stimgen::makeLocalCueboxes(std::vector<int> left_probeorder, std::vector<int> right_probeorder, std::vector<std::vector<sf::Vector2f>> coords, int trialnum);

	sf::RectangleShape stimspace_left = stimspace_gen(-set.stimspace_offset);
	sf::RectangleShape stimspace_right = stimspace_gen(set.stimspace_offset);

	sf::Texture fixtexture = texture_gen("stim\\fixation_cross.png");
	sf::Sprite fixcross = fixationcross_gen();

	sf::Texture lefttexture = texture_gen("stim\\left.png");
	sf::Texture righttexture = texture_gen("stim\\right.png");
	sf::Sprite arrow = arrow_gen();

	sf::Text createinputtext();
	sf::Text createblocktext();
	sf::Text createlocaltext();
	sf::Text createglobaltext();
private:
	sf::RectangleShape boxgen(sf::Color boxcol, sf::Vector2f(position));
	sf::RectangleShape stimspace_gen(float offset);
	std::vector<sf::Vector2f> create_coordinates();
	sf::Sprite fixationcross_gen();
	sf::Sprite arrow_gen();
	sf::Texture texture_gen(const char* imagelocation);
	
};


stimgen::stimgen()
{
}

std::vector<sf::RectangleShape> stimgen::makeboxes(std::vector<std::vector<sf::Vector2f>> coords, std::vector<std::vector<int>> all_colours) {

	std::vector<sf::Vector2f> coordinates = coords[0];
	std::vector<int> col2use = all_colours[0];

	std::vector<sf::RectangleShape> boxes(set.setsize);
	for (size_t i = 0; i < set.setsize; i++) {
		boxes[i] = boxgen(set.colours2use[col2use[i]], coordinates[i]);
	}

	return boxes;
}


std::vector<sf::RectangleShape> stimgen::makefixedboxes(float offset) {

	std::vector<sf::RectangleShape> boxes(set.setsize);


	for (size_t i = 0; i < set.numcols; i++) {
		boxes[i] = boxgen(set.colours2use[i], sf::Vector2f(mon.xcentre + offset, mon.ycentre));
		if (set.debug == true) {
			boxes[i].setOutlineColor(sf::Color::Black);
			boxes[i].setOutlineThickness(5);
		}
	}

	return boxes;
}

std::vector<sf::RectangleShape> stimgen::makeLocalCueboxes(std::vector<int> left_probeorder, std::vector<int> right_probeorder, std::vector<std::vector<sf::Vector2f>> coords, int trialnum) {

	std::vector<sf::RectangleShape> boxes(2);
	std::vector<sf::Vector2f> coordinates = coords[trialnum];

	sf::RectangleShape box = sf::RectangleShape(set.boxsize);;
	if (set.debug == true) {
		box.setOutlineColor(sf::Color::Black);
		box.setOutlineThickness(5);
	}

	box.setOrigin(sf::Vector2f(set.boxcentre));
	box.setPosition(coordinates[0]);
	box.setFillColor(set.colours2use[left_probeorder[trialnum]]);
	boxes[0] = box;

	box.setPosition(coordinates[4]);
	box.setFillColor(set.colours2use[right_probeorder[trialnum]]);
	boxes[1] = box;

	return boxes;
}

std::vector<sf::RectangleShape> stimgen::shuffleboxes(std::vector<sf::RectangleShape> boxes, std::vector<std::vector<sf::Vector2f>> coords, int trialnum, std::vector<std::vector<int>> all_colours) {

	std::vector<sf::Vector2f> coordinates = coords[trialnum];
	std::vector<int> col2use = all_colours[trialnum];

	for (size_t i = 0; i < set.setsize; i++) {
		sf::RectangleShape box = boxes[i];

		box.setPosition(coordinates[i]);
		box.setFillColor(set.colours2use[col2use[i]]);

		boxes[i] = box;
	}

	return boxes;
}

sf::RectangleShape  stimgen::boxgen(sf::Color boxcol, sf::Vector2f(position))
{
	sf::RectangleShape box = sf::RectangleShape(set.boxsize);
	box.setFillColor(boxcol);
	box.setOrigin(set.boxcentre);
	box.setPosition(position);

	return box;
}

sf::Texture stimgen::texture_gen(const char* imagelocation) {
	sf::Texture texture;
	if (!texture.loadFromFile(imagelocation)) {
		std::cout << "error loading Fixation cross" << std::endl;
	}

	return texture;
}

sf::Sprite stimgen::fixationcross_gen() {

	sf::Sprite FixCross;
	FixCross.setOrigin(set.boxcentre);
	FixCross.setPosition(sf::Vector2f(mon.xcentre, mon.ycentre));

	return FixCross;
}


sf::Sprite stimgen::arrow_gen() {

	sf::Sprite arrow;
	arrow.setOrigin(set.boxcentre);
	arrow.setPosition(sf::Vector2f(mon.xcentre, mon.ycentre - set.arrowoffset));

	return arrow;
}


sf::RectangleShape  stimgen::stimspace_gen(float offset)
{
	sf::RectangleShape box = sf::RectangleShape(set.stimspace_size);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2);
	box.setOrigin(set.stimspace_centre);
	box.setPosition(sf::Vector2f(mon.xcentre + offset, mon.ycentre));

	return box;
}


std::vector<sf::Vector2f> stimgen::create_coordinates() {

	//settings
	float xmin1 = mon.xcentre - set.stimspace_centre.x - set.stimspace_offset;	//xmin1
	float xmax1 = mon.xcentre - set.stimspace_offset;								//xmax1
	float xmin2 = mon.xcentre + set.stimspace_offset; 								//xmin2
	float xmax2 = mon.xcentre + set.stimspace_centre.x + set.stimspace_offset; //xmax2
	float ymin = mon.ycentre - set.stimspace_centre.y;							//ymin
	float ymax = mon.ycentre + set.stimspace_centre.y;
	float x;
	float y;
	//setup
	std::vector<sf::Vector2f> coordinates(set.setsize);

	std::uniform_int_distribution<> disx1(xmin1, xmax1);
	std::uniform_int_distribution<> disx2(xmin2, xmax2);
	std::uniform_int_distribution<> disy(ymin, ymax);

	//create null distribution for comparison
	std::vector<sf::Vector2f> nulldist_left(set.setsize / 2);
	std::vector<sf::Vector2f> nulldist_right(set.setsize / 2);

	for (size_t i = 0; i < set.setsize / 2; i++) {
		nulldist_left[i] = sf::Vector2f(0, 0);
		nulldist_right[i] = sf::Vector2f(0, 0);
	}

	//actually create these coordinates

	for (size_t i = 0; i < set.setsize; i++) {

		if (i <set.setsize / 2) { //left

								  //create tooclose vector
			std::vector<int> tooclose(set.setsize / 2);
			for (size_t j = 0; j < set.setsize / 2; j++) {
				tooclose[j] = 0;
			}

			bool proceed = false;
			while (proceed == false) {

				//create some coordinates
				x = round(float(disx1(rng)));
				y = round(float(disy(rng)));

				//is it far enough away from the other blocks?

				for (size_t j = 0; j < set.setsize / 2; j++) {
					float xdist = (x - nulldist_left[j].x) * (x - nulldist_left[j].x);
					float ydist = (y - nulldist_left[j].y) * (y - nulldist_left[j].y);
					float distance = sqrt(xdist + ydist);

					if (distance < set.mindist) { tooclose[j] = 1; }
					else { tooclose[j] = 0; }

				}

				//if none too close, proceed to next object

				if (std::any_of(tooclose.begin(), tooclose.end(), [](int i) {return i > 0; })) {
					proceed = false;
				}
				else {
					nulldist_left[i] = sf::Vector2f(x, y);
					proceed = true;
				}


			}

			coordinates[i] = sf::Vector2f(x, y);
		}
		else { //right

			   //create tooclose vector
			std::vector<int> tooclose(set.setsize / 2);
			for (size_t j = 0; j < set.setsize / 2; j++) {
				tooclose[j] = 0;
			}

			bool proceed = false;
			while (proceed == false) {

				//create some coordinates
				x = round(float(disx2(rng)));
				y = round(float(disy(rng)));

				//is it far enough away from the other blocks?

				for (size_t j = 0; j < set.setsize / 2; j++) {
					float xdist = (x - nulldist_right[j].x) * (x - nulldist_right[j].x);
					float ydist = (y - nulldist_right[j].y) * (y - nulldist_right[j].y);
					float distance = sqrt(xdist + ydist);

					if (distance < set.mindist) { tooclose[j] = 1; }
					else { tooclose[j] = 0; }

				}

				//if none too close, proceed to next object

				if (std::any_of(tooclose.begin(), tooclose.end(), [](int i) {return i > 0; })) {
					proceed = false;
				}
				else {
					nulldist_right[i - set.setsize / 2] = sf::Vector2f(x, y);
					proceed = true;
				}
			}
			coordinates[i] = sf::Vector2f(x, y);
		}
	}


	return coordinates;
}

std::vector<std::vector<sf::Vector2f>> stimgen::create_coordinates_all(std::vector<int> trialtype_all) {

	std::vector<std::vector<sf::Vector2f>> All_coordinates(set.numtrials_total);
	std::vector<sf::Vector2f> tempcoodrs1(set.setsize);
	std::vector<sf::Vector2f> tempcoodrs2(set.setsize);

	for (size_t i = 0; i < set.numtrials_total; i++) {

			All_coordinates[i] = create_coordinates();

	}

	return All_coordinates;
}

sf::Text  stimgen::createblocktext() {
	sf::Font font;
	if (!font.loadFromFile("stim\\GOTHICB.TTF")) {// error...
	}
	sf::Text inputtext;
	inputtext.setFont(font);
	inputtext.setCharacterSize(80);
	inputtext.setString("BLOCK");
	inputtext.setColor(sf::Color::Black);
	inputtext.setPosition(sf::Vector2f(mon.xcentre - 190, mon.ycentre - 100));

	return inputtext;
}

sf::Text  stimgen::createlocaltext() {
	sf::Font font;
	if (!font.loadFromFile("stim\\GOTHICB.TTF")) {// error...
	}
	sf::Text inputtext;
	inputtext.setFont(font);
	inputtext.setCharacterSize(60);
	inputtext.setString("Remember Colours only");
	inputtext.setColor(sf::Color::Black);
	inputtext.setPosition(sf::Vector2f(mon.xcentre - 400, mon.ycentre ));

	return inputtext;
}

sf::Text  stimgen::createglobaltext() {
	sf::Font font;
	if (!font.loadFromFile("stim\\GOTHICB.TTF")) {// error...
	}
	sf::Text inputtext;
	inputtext.setFont(font);
	inputtext.setCharacterSize(60);
	inputtext.setString("Remember Colours and Locations");
	inputtext.setColor(sf::Color::Black);
	inputtext.setPosition(sf::Vector2f(mon.xcentre - 450, mon.ycentre));

	return inputtext;
}


sf::Text  stimgen::createinputtext() {
	sf::Font font;
	if (!font.loadFromFile("stim\\GOTHICB.TTF")) {// error...
	}
	sf::Text inputtext;
	inputtext.setFont(font);
	inputtext.setCharacterSize(80);
	inputtext.setString("0");
	inputtext.setColor(sf::Color::Black);
	inputtext.setPosition(sf::Vector2f(mon.xcentre + 110, mon.ycentre-100));

	return inputtext;
}

std::vector<std::vector<int>> stimgen::create_colour_order(std::vector<int> trialtype) {

	float col2use;
	float col2use2;
	bool proceed;

	std::uniform_int_distribution<> dist(0, 6);
	std::vector<int> coldist = { 0, 1, 2, 3, 4, 5, 6 };
	std::vector<int> coldist2(set.setsize);

	std::vector<std::vector<int>> colours(set.numtrials_total);

	for (size_t j = 0; j < set.numtrials_total; j++) {
		int count = 0;
		switch (trialtype[j]) {

		case 1: //four identical colours
			col2use = float(dist(rng));
			for (size_t i = 0; i < set.setsize / 2; i++) {
				coldist2[i] = int(col2use);
			}

			proceed = false;
			while (proceed == false) {//make sure not the same color on both sides
				col2use2 = float(dist(rng));
				if (col2use2 != col2use) { proceed = true; }
			}

			for (size_t i = size_t(set.setsize) / 2; i < set.setsize; i++) {
				coldist2[i] = int(col2use2);
			}
			colours[j] = coldist2;
			break;


		case 2: //two colours
			//side 1
			col2use = float(dist(rng));
			for (size_t i = 0; i < set.setsize/4; i++) {
				coldist2[i] = int(col2use);
			}

			proceed = false;
			while (proceed == false) { //make sure not the same color for both
				col2use2 = float(dist(rng));
				if (col2use2 != col2use) { proceed = true; }
			}

			for (size_t i = size_t(set.setsize) / 4; i < set.setsize / 2; i++) {
				coldist2[i] = int(col2use2);
			}

			// side 2
			std::random_shuffle(coldist.begin(), coldist.end(), myrandom);


			for (size_t i = 0; i < (set.setsize-1); i+=2) {
				coldist2[i] = coldist[count];
				coldist2[i+1] = coldist[count];
				count++;
			}

			//set colors
			colours[j] = coldist2;
			break;

		
		case 3: //four unique colours
			std::random_shuffle(coldist.begin(), coldist.end(), myrandom);
			for (size_t i = 0; i < set.setsize/2; i++) {
				coldist2[i] = coldist[i];
			}

			std::random_shuffle(coldist.begin(), coldist.end(), myrandom);
			for (size_t i = size_t(set.setsize) / 2; i < set.setsize; i++) {
				coldist2[i] = coldist[i- set.setsize / 2];
			}

			colours[j] = coldist2;
			break;
		}

	}

	return colours;
}
