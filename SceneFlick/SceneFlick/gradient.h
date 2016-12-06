#pragma once
#include <SFML/Graphics.hpp>

sf::Color Red = sf::Color(255, 0, 0, 127);
sf::Color Blue = sf::Color(0, 0, 255, 127);
sf::Color Black = sf::Color(0, 0, 0, 0);

double pi = 3.1415926535;

double Lum;
double a = 255 / 2;


// settings
settings set;

class gradient : public sf::Drawable, public sf::Transformable
{
public:

	//gradient();

	bool makesquares(int width, int height, int numsquares_x, int numsquares_y) {

		

		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(numsquares_x * numsquares_y * 4);
		sf::Vector2i tileSize = { width / numsquares_x, height / numsquares_y };


		for (int i = 0; i < numsquares_x; ++i)
			for (int j = 0; j < numsquares_y; ++j)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * numsquares_x) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			}
		return true;
	}

	void flick(int framecount, int numsquares_x, int numsquares_y, double x) {
		int block = 0;
		for (int i = 0; i <numsquares_y; i++) {
			for (unsigned int j = 0; j < numsquares_x; ++j)
			{
				double Hz = set.genset.frequencies[block];
				Lum = a*sin(2 * pi * Hz*x - pi) + a;
				colorsquaresS(numsquares_x, numsquares_y, Lum, j, i);
				block++;
			}
		}
	}


private:


	bool colorsquaresS(unsigned int numsquares_x, unsigned int numsquares_y, int alpha, unsigned int i, unsigned int j) {

		sf::Vertex* quad = &m_vertices[(i + j * numsquares_x) * 4];
		for (int k = 0; k < 4; k++) {
				quad[k].color = sf::Color(0,0, 0, alpha);
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