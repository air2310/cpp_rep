#pragma once
#include <SFML/Graphics.hpp>
#include "flicker.h"
#include "gamefunctions.h"

sf::Color Red = sf::Color(255, 0, 0, 127);
sf::Color Blue = sf::Color(0, 0, 255, 127);
sf::Color Black = sf::Color(0, 0, 0, 0);

struct CLUT
{
	std::vector<double> green = makeclut("CLUT_green_rgb.txt");
	std::vector<double> magenta = makeclut("CLUT_magenta_rgb.txt");
	std::vector<double> white = makeclut("CLUT_white_rgb.txt");
}; CLUT clut;

class gradient : public sf::Drawable, public sf::Transformable
{
public:

	//gradient();

	bool makesquares(int width, int height, int numsquares, int xxtra) {

		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(numsquares * numsquares * 4);
		sf::Vector2i tileSize = { width / numsquares, height / numsquares };


		for (int i = 0; i < numsquares; ++i)
			for (int j = 0; j < numsquares; ++j)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * numsquares) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x +xxtra, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x + xxtra, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x + xxtra, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x + xxtra, (j + 1) * tileSize.y);

			}
		return true;
	}

	void flick(std::vector<std::vector<double>> FLICKS, int framecount, int numsquares, int axis, flicktype flick2use) {
		for (int H = 0; H < numsquares; H++) {
			std::vector<double> flickrate = FLICKS[H];
			for (unsigned int j = 0; j < numsquares; ++j)
			{
				switch (axis) {
				case 1:
					switch (flick2use) {
					case flicktype::blink:
						colorsquaresB(numsquares, flickrate[framecount]*axis, j, H);
						break;
					case flicktype::smooth:
						colorsquaresS(numsquares, flickrate[framecount], j, H, axis);
						break;
					}
					break;
				case 2:
					switch (flick2use) {
					case flicktype::blink:
						colorsquaresB(numsquares, flickrate[framecount] * axis, H, j);
						break;
					case flicktype::smooth:
						colorsquaresS(numsquares, flickrate[framecount], H, j, axis);
						break;
					}
				}
			}
		}
	}

	void flicksingle(std::vector<std::vector<double>> FLICKS, int framecount, int numsquares, int axis, flicktype flick2use) {
		for (int H = 0; H < numsquares; H++) {
			std::vector<double> flickrate = FLICKS[H];
				colorsquaresS(numsquares, flickrate[framecount], axis - 1, H, 3);

				switch (axis) { // make unused spot transparent
				case 1:
					colorsquaresS(numsquares, flickrate[framecount],1, H, 4);
					break;
				case 2:
					colorsquaresS(numsquares, flickrate[framecount], 0, H, 4);
					break;
				}

		}
	}

	void flicknoalph(std::vector<std::vector<double>> FLICKSX, std::vector<std::vector<double>> FLICKSY, int framecount, int numsquares, int axis, flicktype flick2use) {
		std::vector<double> flickratey;
		std::vector<double> flickratex;
		for (int i = 0; i < numsquares; i++) 
			for (int j = 0; j < numsquares; j++) {
				flickratex = FLICKSX[i];
				flickratey = FLICKSY[j];
				colorsquaresS_noalph(numsquares, flickratex[framecount], flickratey[framecount], i, j);
		}
	}

private:

	//bool colorsquaresB(unsigned int numsquares, int col, unsigned int i, unsigned int j );

	bool colorsquaresB(unsigned int numsquares, int col, unsigned int i, unsigned int j ) {

		sf::Vertex* quad = &m_vertices[(i + j * numsquares) * 4];

		for (int k = 0; k < 4; k++) {
			switch (col) {
			case 0:
				quad[k].color = Black;
				break;
			case 1:
				quad[k].color = Red;
				break;
			case 2:
				quad[k].color = Blue;
				break;
			}
		}
		//quad[0].color = Black;

		return 0;
	}

	bool colorsquaresS(unsigned int numsquares, int alpha, unsigned int i, unsigned int j, int axis) {

		sf::Vertex* quad = &m_vertices[(i + j * numsquares) * 4];
		int lum = round(alpha);

		for (int k = 0; k < 4; k++) {
			switch (axis) {
			case 1:
				/*quad[k].color = sf::Color(255, 0, 255, alpha);*/
				//quad[k].color = sf::Color(clut.magenta[lum], 0, clut.magenta[lum], 255);
				quad[k].color = sf::Color(clut.magenta[lum], 0, clut.magenta[lum], clut.magenta[lum] );
				//quad[k].color = sf::Color(clut.magenta[lum], 0, clut.magenta[lum], clut.magenta[lum]/2);
				break;
			case 2:
				//quad[k].color = sf::Color(0, clut.green[lum], 0, 127.5);
				quad[k].color = sf::Color(0, clut.green[lum], 0, clut.green[lum]);
				//quad[k].color = sf::Color(0, clut.green[lum], 0, clut.green[lum] / 2);
				break;
			case 3:
				quad[k].color = sf::Color(clut.white[lum], clut.white[lum], clut.white[lum], 255);
				break;
			case 4:
				quad[k].color = sf::Color(0, 0, 0, 0);
				break;
			}


		}

		return 0;
	}

	bool colorsquaresS_noalph(unsigned int numsquares, int alphax, int alphay, unsigned int i, unsigned int j) {

		sf::Vertex* quad = &m_vertices[(i + j * numsquares) * 4];
		int lumx = round(alphax);
		int lumy = round(alphay);

		for (int k = 0; k < 4; k++) {
				quad[k].color = sf::Color(clut.magenta[lumy], clut.green[lumx], clut.magenta[lumy]);
		}
		//clut.green[lumy]
		return 0;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw the vertex array
		target.draw(m_vertices, states);
	}


	sf::VertexArray m_vertices;
};