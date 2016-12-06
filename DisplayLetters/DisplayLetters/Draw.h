#pragma once
#pragma comment(lib, "sfml-graphics-d.lib")
#include <vector>


sf::Text genletter(char* character) {

	sf::Text letter;
	letter.setCharacterSize(60);
	letter.setString(character);
	letter.setColor(sf::Color::White);
	letter.setPosition(sf::Vector2f(mon.xcentre-30,mon.ycentre-30));

	return letter;
}

std::vector<sf::Text> genLetters() {
	std::vector<sf::Text> Letters(40);

	Letters[0] = genletter("A");	Letters[8] = genletter("I");	Letters[16] = genletter("Q");	Letters[24] = genletter("Y");	Letters[32] = genletter("6");
	Letters[1] = genletter("B");	Letters[9] = genletter("J");	Letters[17] = genletter("R");	Letters[25] = genletter("Z");	Letters[33] = genletter("7");
	Letters[2] = genletter("C");	Letters[10] = genletter("K");	Letters[18] = genletter("S");	Letters[26] = genletter("0");	Letters[34] = genletter("8");
	Letters[3] = genletter("D");	Letters[11] = genletter("L");	Letters[19] = genletter("T");	Letters[27] = genletter("1");	Letters[35] = genletter("9");
	Letters[4] = genletter("E");	Letters[12] = genletter("M");	Letters[20] = genletter("U");	Letters[28] = genletter("2");	Letters[36] = genletter(" ");
	Letters[5] = genletter("F");	Letters[13] = genletter("N");	Letters[21] = genletter("V");	Letters[29] = genletter("3");	Letters[37] = genletter(",");
	Letters[6] = genletter("G");	Letters[14] = genletter("O");	Letters[22] = genletter("W");	Letters[30] = genletter("4");	Letters[38] = genletter(".");
	Letters[7] = genletter("H");	Letters[15] = genletter("P");	Letters[23] = genletter("X");	Letters[31] = genletter("5");	Letters[39] = genletter("<-");

	return Letters;
}

void drawLetters(sf::RenderWindow* window) {

	sf::Font font;
	if (!font.loadFromFile("C:\\Users\\uqarento\\Documents\\Visual Studio 2015\\Projects\\DisplayLetters\\x64\\Debug\\stim\\arial.ttf")) {// error...
	}

	std::vector<sf::Text> Letters = genLetters();
	for (size_t i = 0; i < 40; i++) {
		Letters[i].setFont(font);
	}

	result = 1;
	while (window->isOpen())
	{

		window->clear(sf::Color::Black);

		//window->draw(letter);
		window->draw(Letters[result-1]);
		window->display();
	}
}