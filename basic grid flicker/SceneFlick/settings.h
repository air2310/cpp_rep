#pragma once
#include <SFML/Graphics.hpp>;


class settings {
public:
	struct screen {
		sf::VideoMode size = sf::VideoMode::getDesktopMode();

		sf::Vector2f monsize = sf::Vector2f(float(size.width), float(size.height));
		sf::Vector2f moncentre = sf::Vector2f(float(size.width) / 2, float(size.height) / 2);


	}; 
	screen mon;

	struct TIMING { //seconds

		float monRef = 144.f;

		float trial = 10.0f;
		float rest = 1.0f;
		float trialTotal = trial + rest;

		float fTrial = trial*monRef;
		float fRest = rest*monRef;
		float fTrialTotal = (trialTotal)*monRef;

		float fTrialMicro = trial * 1000000.0f;
		float fTrialTotalMicro = trialTotal * 1000000.0f;

	}; TIMING timing;

	struct general {

		sf::Vector2f numSquares = sf::Vector2f(8, 5);
		float numBlocks = 8;

		bool triggers = false;

		int nFreqs = 40;

		std::vector<float> makeFreqs(int nFreqs) {
			std::vector<float> frequencies(nFreqs);

			float FF = 8.0f;

			for (size_t i = 0; i < nFreqs; i++) {
				frequencies[i] = FF;
				FF = FF + 0.2f;
			}
			return frequencies;
		}

		std::vector<float> frequencies = makeFreqs(nFreqs);


		std::vector<float> makePhase(int nFreqs) {
			std::vector<float> phase(nFreqs);

			phase = { 0.00f, 0.35f, 0.70f,1.05f,1.40f, 1.75f,0.10f,0.45f,0.80f,1.15f,1.50f,1.85f,0.20f,0.55f,0.90f,1.25f,1.60f,1.95f,0.30f,0.65f
				,1.00f,1.35f,1.70f,0.05f,0.40f,0.75f,1.10f,1.45f,1.80f,0.15f,0.50f,0.85f,1.20f,1.55f,1.90f,0.25f,0.60f,0.95f,1.30f,1.65f };

			return phase;
		}
		std::vector<float> phases = makePhase(nFreqs);

		sf::Vector2f boxsize = sf::Vector2f(300, 300); 
		sf::Vector2f boxcentre = sf::Vector2f(boxsize.x/2, boxsize.y/2 );

	}; general genset;
	

};


