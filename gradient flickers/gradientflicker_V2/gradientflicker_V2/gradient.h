#pragma once
#include <SFML/Graphics.hpp>
#include "flicker.h"

sf::Color Red = sf::Color(255, 0, 0, 127);
sf::Color Blue = sf::Color(0, 0, 255, 127);
sf::Color Black = sf::Color(0, 0, 0, 0);

class gradient : public sf::Drawable, public sf::Transformable
{
public:

	//gradient();

	bool makesquares(int width, int height, int numsquares) {

		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(numsquares * numsquares * 4);
		sf::Vector2i tileSize = { width / numsquares, height / numsquares };


		for (int i = 0; i < numsquares; ++i)
			for (int j = 0; j < numsquares; ++j)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * numsquares) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			}
		return true;
	}

	void flick(std::vector<std::vector<int>> FLICKS, int framecount, int numsquares, int axis, flicktype flick2use) {
		for (int H = 0; H < numsquares; H++) {
			std::vector<int> flickrate = FLICKS[H];
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

		for (int k = 0; k < 4; k++) {
			switch (axis) {
			case 1:
				quad[k].color = sf::Color(255, 0, 0, alpha);
				break;
			case 2:
				quad[k].color = sf::Color(0, 255, 0, alpha);
				break;
			}


		}

		return 0;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw the vertex array
		target.draw(m_vertices, states);
	}


	sf::VertexArray m_vertices;
};