#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <numeric>      // std::accumulate

#define PI 3.14159265
#include "painting.h"

;  typedef std::vector<int> Row;
int myrandom(int i) { return std::rand() % i; }

// Settings 

int nShip = 71; // Ship Size
int nAst = 36;
int AstSpeed = 3;

int refreshrate = 60;

int choosenFrames(int refreshrate) {
	
	if (refreshrate == 60) {
		int nFrames = 900;
		return nFrames;
	}
	else if (refreshrate == 120) {
		int nFrames = 1800;
		return nFrames;
	}
	return 0;
}

int nFrames = choosenFrames(refreshrate);

//ScreenSize
class sizes {
public:
	int nWidth = 1000;
	int nHeight = 1000;
	int xxtra = (nWidth - nHeight) / 2;
	int border = 8;
};
sizes screen;

// Set up ColCond
int nCond = 6;
int nBlocks = 12;

std::vector<int> Createorder(int nBlocks, int nCond, int myrandom(int i)) {
	std::srand(unsigned(std::time(0))); //randomiser
	std::vector<int> Order(nBlocks);
	int count = 0;
	for (int T = 0; T < floor(nBlocks / nCond); T++) {
		for (int C = 0; C <nCond; C++) {
			Order[count] = C;
			count = count++;
		}
	}

	if ((nCond*floor(nBlocks / nCond)) < nBlocks) {
		int count = nCond*floor(nBlocks / nCond);
		int start = count;
		for (int C = start; C < nBlocks; C++) {
			Order[count] = rand() % 6;
			count = count++;
		}
	}

	std::random_shuffle(Order.begin(), Order.end(), myrandom); //randomly shuffle elements

	return Order;
}


// Set up colours of asteroids

std::vector<double> create_ACol(const size_t N) { //Lets try figure out which color repeats
	std::vector<double> ACol(N);
	for (size_t i = 0; i < N; i++) {
		if (i < N / 3) {
			ACol[i] = 1;
		}
		else if ((i >((N / 3) - 1)) && (i < (N / 3) * 2)) {
			ACol[i] = 2;
		}
		else if ((i >((N / 3) - 1) * 2) && (i < N)) {
			ACol[i] = 3;
		}
	}

	std::srand(unsigned(std::time(0))); //randomiser
	std::random_shuffle(ACol.begin(), ACol.end(), myrandom); //randomly shuffle elements
	return ACol;
}

std::vector<double> ACol = create_ACol(nAst);


// Set Asteroids up

std::vector<int> CreateAstAngles(int nAst) {
	std::srand(unsigned(std::time(0))); //randomiser

	std::vector<int> AstAngles(nAst);

	for (int A = 0; A < nAst; A++) {
		AstAngles[A] = rand() % 360 + 1;
	}
	return AstAngles;
}
std::vector<int> AstAngles = CreateAstAngles(nAst); //get movement angles

std::vector<double> CreateXinc(int nAst) {
	std::vector<double> Xinc(nAst);
	for (int A = 0; A < nAst; A++) {
		Xinc[A] = cos(AstAngles[A] * (PI / 180.0))*AstSpeed;
	}
	return Xinc;
}
std::vector<double> Xinc = CreateXinc(nAst);

std::vector<double> CreateYinc(int nAst) {
	std::vector<double> Yinc(nAst);
	for (int A = 0; A < nAst; A++) {
		Yinc[A] = sin(AstAngles[A] * (PI / 180.0))*AstSpeed;
	}
	return Yinc;
}
std::vector<double> Yinc = CreateYinc(nAst);


std::vector<Row> AstX = PreAllocateAst(nAst, nFrames, screen.nHeight, screen.nHeight, nShip, AstSpeed, Xinc);
std::vector<Row> AstY = PreAllocateAst(nAst, nFrames, screen.nHeight, screen.nHeight, nShip, AstSpeed, Yinc); //This is such a dodgy workaround, fix it by just tossing out x and y and only calculating one. Seriously!!!!!!!!!

// Contact matrices

extern std::vector<Row> ContactP = ContactMatrix(nFrames, nBlocks);
std::vector<Row> ContactN = ContactMatrix(nFrames, nBlocks);
std::vector<Row> ContactNu = ContactMatrix(nFrames, nBlocks);



int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(screen.nWidth, screen.nHeight), "ASTEROIDS");
	window.setFramerateLimit(refreshrate);
	ShowCursor(FALSE);//hides the cursor
	std::vector<Row> ColorCond = CreateColorCond();
	std::vector<int> Order = Createorder(nBlocks, nCond, myrandom); //get movement angles



	sf::Texture texture;
	if (!texture.loadFromFile("stars.bmp")) {}

	sf::Sprite stars;
	stars.setTexture(texture);

	sf::Font font;
	if (!font.loadFromFile("impact.ttf"))
	{
		// error...
	}


	sf::Text health;
	health.setString("APPROACH");
	health.setFont(font); // font is a sf::Font
	health.setCharacterSize(60); // in pixels, not points!
	health.setColor(sf::Color::White);
	health.setPosition(sf::Vector2f(float(screen.nWidth/2-300), float(screen.nHeight/2 - 100))); // absolute position

	sf::Text damage;
	damage.setString("AVOID");
	damage.setFont(font); // font is a sf::Font
	damage.setCharacterSize(60); // in pixels, not points!
	damage.setColor(sf::Color::White);
	damage.setPosition(sf::Vector2f(float(screen.nWidth / 2 - 200), float(screen.nHeight / 2 + 0))); // absolute position

	sf::Text total;
	total.setString("TOTAL");
	total.setFont(font); // font is a sf::Font
	total.setCharacterSize(60); // in pixels, not points!
	total.setColor(sf::Color::White);
	total.setPosition(sf::Vector2f(float(screen.nWidth / 2 - 200), float(screen.nHeight / 2 + 125))); // absolute position

	sf::RectangleShape rectangle(sf::Vector2f(470, 5));
	rectangle.setFillColor(sf::Color(255, 255, 255));
	rectangle.setPosition(sf::Vector2f(float(screen.nWidth / 2 - 210), float(screen.nHeight / 2 + 100))); // absolute position
	

	sf::Texture commet;
	if (!commet.loadFromFile("commetW.png"))
	{
	}
	
	sf::Sprite COMMET;
	COMMET.setTexture(commet);
	COMMET.setScale(sf::Vector2f(0.15f, 0.15f)); // absolute scale factor

	sf::Texture rock;
	if (!rock.loadFromFile("rock.png"))
	{
	}

	std::vector<sf::Sprite> Asteroids(nAst);
	for (int A = 0; A < nAst; A++) {
		Asteroids[A].setTexture(rock);
		Asteroids[A].setScale(sf::Vector2f(0.35f, 0.35f)); // absolute scale factor 0.28
		Asteroids[A].setOrigin(128, 128);
		Asteroids[A].setRotation(float(rand() % 361));
		if (ACol[A] == 1) {
			Asteroids[A].setColor(sf::Color(255, 0, 0));
		}
		if (ACol[A] == 2) {
			Asteroids[A].setColor(sf::Color(0, 255, 0));
		}
		if (ACol[A] == 3) {
			Asteroids[A].setColor(sf::Color(0, 0, 255));
		}
	}

	

	int Framecount = 0;
	int A = 0;
	int Trial = 0;

	sf::Clock clock;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
			int condition = Order[Trial];

			sf::Sprite healthrock;
			healthrock.setTexture(rock);
			healthrock.setScale(sf::Vector2f(0.28f, 0.28f));
			healthrock.setPosition(sf::Vector2f(float(screen.nWidth / 2 + 25), float(screen.nHeight / 2 - 100))); // absolute position

			switch (ColorCond[condition][0]) {
			case 1: {
				healthrock.setColor(sf::Color(255, 0, 0)); break; }
			case 2: {
				healthrock.setColor(sf::Color(0, 255, 0)); break; }
			case 3: {
				healthrock.setColor(sf::Color(0, 0, 255)); break; }
			}

			sf::Sprite damagerock;
			damagerock.setTexture(rock);
			damagerock.setScale(sf::Vector2f(0.28f, 0.28f));
			damagerock.setPosition(sf::Vector2f(float(screen.nWidth / 2 + 25), float(screen.nHeight / 2 + 0))); // absolute position

			switch (ColorCond[condition][1]) {
			case 1: {
				damagerock.setColor(sf::Color(255, 0, 0)); break; }
			case 2: {
				damagerock.setColor(sf::Color(0, 255, 0)); break; }
			case 3: {
				damagerock.setColor(sf::Color(0, 0, 255)); break; }
			}
		
		
		// Cue
		
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed < sf::seconds(4)) {
			// clear the window with black color
			window.clear(sf::Color::Black);
			window.draw(stars);
			window.draw(health);
			window.draw(healthrock);
			window.draw(damage);
			window.draw(damagerock);
		}

		else if (Framecount == nFrames - 1) {
			if (elapsed < sf::seconds(23)) {
				// Feedback 

				std::vector<int> CP = ContactP[Trial];
				int posContact = std::accumulate(CP.rbegin(), CP.rend(), 0);
				int Ppoints = ((posContact * 100) / nFrames)-100;
				char str[4]; 	memset(str, '\0', sizeof(str));
				sprintf_s(str, "%d", Ppoints);

				sf::Text Pcont;
				Pcont.setString(str);
				Pcont.setFont(font); // font is a sf::Font
				Pcont.setCharacterSize(60); // in pixels, not points!
				Pcont.setColor(sf::Color::White);
				Pcont.setPosition(sf::Vector2f(float(screen.nWidth / 2 + 150), float(screen.nHeight / 2 - 100))); // absolute position

				std::vector<int> CN = ContactN[Trial];
				int negContact = std::accumulate(CN.rbegin(), CN.rend(), 0);
				int Npoints = (-((negContact * 100) / nFrames)*10)+100;
				if (Npoints < 0) {
					Npoints = 0;
				}
				char strN[5];	memset(strN, '\0', sizeof(strN));
				sprintf_s(strN, "%d", Npoints);

				sf::Text Ncont;
				Ncont.setString(strN);
				Ncont.setFont(font); // font is a sf::Font
				Ncont.setCharacterSize(60); // in pixels, not points!
				Ncont.setColor(sf::Color::White);
				Ncont.setPosition(sf::Vector2f(float(screen.nWidth / 2 + 150), float(screen.nHeight / 2 + 0))); // absolute position

				int Tpoints = Npoints + Ppoints;
				char strT[6];	memset(strT, '\0', sizeof(strT));
				sprintf_s(strT, "%d", Tpoints);

				sf::Text totalS;
				totalS.setString(strT);
				totalS.setFont(font); // font is a sf::Font
				totalS.setCharacterSize(60); // in pixels, not points!
				totalS.setColor(sf::Color::White);
				totalS.setPosition(sf::Vector2f(float(screen.nWidth / 2 + 150), float(screen.nHeight / 2 + 125))); // absolute position

				window.clear(sf::Color::Black);

				window.draw(stars);
				window.draw(health);
				window.draw(healthrock);
				window.draw(damage);
				window.draw(damagerock);
				window.draw(total);
				window.draw(Pcont);
				window.draw(Ncont);
				window.draw(totalS);
				window.draw(rectangle);
				
			}
			else {
				Framecount = 0;
				clock.restart();
				Trial++;
				if (Trial == nBlocks) {
					break;
				}
			}
			//break;
		}
		else if (elapsed >= sf::seconds(4) ) {
			//Trial
			Framecount = Framecount++;

			window.clear(sf::Color::Black);

			window.draw(stars);

			COMMET.setOrigin(500, 500);
			COMMET.rotate(18);
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			COMMET.setPosition(sf::Vector2f(localPosition)); // absolute position
			COMMET.setColor(sf::Color(128, 128, 128));

			for (int A = 0; A < nAst; A++) {
				Asteroids[A].setPosition(sf::Vector2f(float(AstX[A][Framecount]), float(AstY[A][Framecount]))); // absolute position
				window.draw(Asteroids[A]);

				if ((localPosition.x+75 > AstX[A][Framecount]) & (localPosition.x + 75<AstX[A][Framecount] + 100) & (localPosition.y + 75>AstY[A][Framecount]) & (localPosition.y + 75 < AstY[A][Framecount] + 100)) {
					if (ACol[A] == ColorCond[condition][0]) {
						COMMET.setColor(sf::Color(255, 255, 255)); 
						++ContactP[Trial][Framecount]; 
					}
					
					if (ACol[A] == ColorCond[condition][1]) {
						COMMET.setColor(sf::Color(0, 0, 0));
						++ContactN[Trial][Framecount];
					}
					if (ACol[A] == ColorCond[condition][2]) {
						++ContactNu[Trial][Framecount];
					}
				}
			}
			
			window.draw(COMMET);
			
		}

		// end the current frame
		window.display();


	}

	ShowCursor(TRUE);
	return 0;
}