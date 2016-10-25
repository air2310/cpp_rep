#pragma once

double pi = 3.1415926535;


struct screen {
	sf::VideoMode size = sf::VideoMode::getDesktopMode();

	float width = float(size.width);
	float height = float(size.height);

	float xcentre = width / 2;
	float ycentre = height / 2;

	int ref = 60;

}; screen mon;

struct TIMING { //seconds

	float trialnum = 1;
	float cue = 1;
	float BarRot = 6;

	float sum_trialnum = trialnum;
	float sum_cue = trialnum + cue;
	float sum_BarRot = trialnum + cue + BarRot;
	float sum_cue2 = trialnum + cue + BarRot + cue;
	float sum_BarRot2 = trialnum + cue + BarRot + cue + BarRot;

}; TIMING timing;

struct general {

	float patchsize = 200;
	float patchcentre = patchsize ;

	float barheight = 400;
	float barwidth = 10;
	sf::Vector2f barcentre = sf::Vector2f(barwidth / 2, barheight / 2);

	float BarRotAng = 180/ timing.BarRot;

	float fontsize = 100;
	sf::Vector2f fontcentre = sf::Vector2f(0, fontsize / 2);

	std::vector<float> angles2cue = { 45, 90, 135 };
	std::vector<int> triggeroptions = { 101, 102, 103, 201, 202, 203, 10, 21, 25  };
	//std::vector<char> triggeroptions = { "rotating bar 45deg","rotating bar 90deg", "rotating bar 135deg", "Imag bar 45deg","Imag bar 90deg", "Imag bar 135deg", "Trialnum", "BarCue", "ImagCue"};

	float numtrials = 99;

	bool triggers = false;
}; general set;



struct flicktime {
	float trial = mon.ref*(timing.BarRot + 2); //seconds

	int alphavar = 255 / 2;
	double Hz = 12;

}; 	flicktime f;