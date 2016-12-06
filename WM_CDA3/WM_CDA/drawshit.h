#pragma once

#include <iostream>
#include <Windows.h>

#include "settings.h"
#include "stimgen.h"
#include "gamelogic.h"
#include "writetxt.h"
#include "triggers.h"

// ## timing settings ##
sf::Clock clock1;
sf::Clock clock2;
sf::Clock RTclock;
sf::Time elapsed;
sf::Time refresh;
sf::Time RT;

std::vector<sf::Int64> framerate(f.trial);

// ## triggers ##
struct triggers {
	int block = 1;
	std::vector<int> side = { 21, 22 };
	std::vector<int> trialtypeArray = { 51, 52, 53 };
	std::vector<int> trialtypeDelay = { 101, 102, 103 };
	std::vector<int> probe = { 201, 202 };
	int null = 0;

}; triggers trig;

void draw_shit(sf::RenderWindow* window) {

	// ## setup game logic ##
	std::vector<int> cuetype_all = create_cuetype_all();
	std::vector<int> trialtype = create_trialtype(cuetype_all);
	std::vector<int> cuedside = create_cuedside_all(trialtype, cuetype_all);
	std::vector<int> respones = create_responses();
	std::vector<float> RTvec = create_RTvec();
	std::vector<float> accuracyvec = create_accuracyvec();
	std::vector<int> blocktrials = create_blocktrials();

	stimgen stim;
	std::vector<std::vector<sf::Vector2f>> all_coordinates = stim.create_coordinates_all(trialtype);
	std::vector<std::vector<int>> all_colours = stim.create_colour_order(trialtype);

	std::vector<int> probefidelity_cued = create_probefidelity_all(trialtype, cuedside, cuetype_all);
	std::vector<int> probefidelity_uncued = create_probefidelity_all(trialtype, cuedside, cuetype_all);

	std::vector<int> left_probeorder = create_probeorder(cuedside, probefidelity_cued, probefidelity_uncued, 1, all_colours, cuetype_all); //left
	std::vector<int> right_probeorder = create_probeorder(cuedside, probefidelity_cued, probefidelity_uncued, 2, all_colours, cuetype_all); //right

	std::vector<int> onset_jitter = create_onset_jitter();

	// ## get participant number ##
	int ID_idx; //participant ID
	std::vector<char*> Pids = createPid();
	std::vector<char*> PidsDir = createPidDir();
	std::cout << "Enter Participant Number: ";
	std::cin >> ID_idx;
	char* ID = Pids[ID_idx];
	char* dataDirectR = PidsDir[ID_idx];

	// ## save game logic ##
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "Saving Information:" << std::endl;

	writetxt(all_coordinates, all_colours, trialtype, cuedside, probefidelity_cued, probefidelity_uncued, left_probeorder, right_probeorder, blocktrials, cuetype_all, ID, dataDirectR);

	// ## things to draw ##
	std::vector<sf::RectangleShape> boxes = stim.makeboxes(all_coordinates, all_colours);

	std::vector<sf::RectangleShape> boxes_fixedleft = stim.makefixedboxes(-set.stimspace_offset);
	std::vector<sf::RectangleShape> boxes_fixedright = stim.makefixedboxes(set.stimspace_offset);

	sf::Sprite fixcross = stim.fixcross; fixcross.setTexture(stim.fixtexture);
	sf::Sprite left = stim.arrow; left.setTexture(stim.lefttexture);
	sf::Sprite right = stim.arrow; right.setTexture(stim.righttexture);

	sf::Text blocktext = stim.createblocktext();
	sf::Text inputtext = stim.createinputtext();
	sf::Text globaltext = stim.createglobaltext();
	sf::Text localtext = stim.createlocaltext();
	sf::Font font;
	if (!font.loadFromFile("stim\\GOTHICB.TTF")) {}
	inputtext.setFont(font);
	blocktext.setFont(font);
	globaltext.setFont(font);
	localtext.setFont(font);

	// ## initialise counts ##
	int framecount = 0;
	int trialcount = 0;
	int blockcount = 0;

	bool noresponse = true;
	bool epochstart = true;

	trialperiod period = trialperiod::rest;


	// ## initialise boxes ##
	boxes = stim.shuffleboxes(boxes, all_coordinates, trialcount, all_colours);
	std::vector<sf::RectangleShape> LocalCueboxes = stim.makeLocalCueboxes(left_probeorder,right_probeorder, all_coordinates, trialcount);

	// ## initialise saving ##
	std::string responseFileName = makefilename(dataDirectR, "Responses", ID);
	std::ofstream response_file;
	response_file.open(responseFileName);
	response_file << "Trial" << '\t' << "Response" << '\t' << "RT" << '\t' << "Accuracy" << std::endl;
	response_file.close();

	// ## display info ##
	std::cout << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::cout << "Trial: " << trialcount + 1 << " Arraytype: " << trialtype[trialcount] << std::endl;

	const char* dir = "";

	const char* probefid = "";
	switch (cuedside[trialcount]) {
	case 1: dir = "Left"; break;
	case 2: dir = "Right"; break;
	}

	switch (probefidelity_cued[trialcount]) {
	case 0: probefid = "absent"; break;
	case 1: probefid = "present"; break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	std::cout << "	Cue Direction: " << dir <<
		"	Target: " << probefid << std::endl; // display some data


	// ## triggers ##
	if (set.opt_triggers == true) {
		trigger(trig.null);
	}

	bool trigblock = true;
	std::vector<int> trigtrial = { 1, 1, 1,1 };

	// #### begin! ####
	while (window->isOpen())
	{

		window->clear(sf::Color(128, 128, 128));

		// ## refresh timing ##
		refresh = clock1.restart();

		switch (period) {
			// #### block rest ####
		case trialperiod::rest:
			// ## trigger ##
			if (set.opt_triggers == true) {
				if (trigblock == true) {
					trigger(trig.block + blockcount);
					trigger(0);
					trigblock = false;
				}
			}

			elapsed = clock2.getElapsedTime();

			// ## create block text ##
			char str[6]; 	memset(str, '\0', sizeof(str));
			sprintf_s(str, "%d", blockcount + 1);
			inputtext.setString(str);

			// ## present text ##
			window->draw(blocktext);
			window->draw(inputtext);

			switch (cuetype_all[trialcount]) {
			case 0: window->draw(globaltext);
				break;
			case 1: window->draw(localtext);
				break;
			}

			// ## move on ##
			if (set.autoblockprogress == true) {
				if (elapsed.asSeconds() > timing.blockrest) {
					period = trialperiod::trial;
					clock2.restart();
					trigblock = true;
				}
			}
			else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					period = trialperiod::trial;
					clock2.restart();
					trigblock = true;
				}
			}
		break;

		// #### Trial Period! ####
		case trialperiod::trial:

			// ## setup trial timing ##
			elapsed = clock2.getElapsedTime();

			// #### Direction Cue ####
			if (elapsed.asMilliseconds() < timing.cue) {
				// ## trigger ##
				if (set.opt_triggers == true) {
					if (trigtrial[0] == 1) {
						trigger(trig.side[cuedside[trialcount]]);
						trigger(0);
						std::cout << trig.side[cuedside[trialcount] - 1] << std::endl;
						trigtrial[0] = 0;
					}
				}

				// ## Draw ##
				window->draw(fixcross);

				switch (cuedside[trialcount]) {
				case 1: //left
					window->draw(left);
					break;
				case 2: //right
					window->draw(right);
					break;

				}
			}

			// #### wait period ####
			else if (elapsed.asMilliseconds() < timing.cue + onset_jitter[trialcount]) {
				window->draw(fixcross);
			}

			// #### Present memory Array ####
			else if (elapsed.asMilliseconds() < timing.cue + onset_jitter[trialcount] + timing.memory_array) {
				// ## trigger ##
				if (set.opt_triggers == true) {
					if (trigtrial[1] == 1) {
						trigger(trig.trialtypeArray[trialtype[trialcount]]);
						trigger(0);
						trigtrial[1] = 0;
					}
				}

				// ## draw ##
				window->draw(fixcross);

				for (size_t i = 0; i < set.setsize; i++) {
					window->draw(boxes[i]);
				}
			}

			// #### memory CDA period ####
			else if (elapsed.asMilliseconds() < timing.cue + onset_jitter[trialcount] + timing.memory_array + timing.interval2) {
				// ## trigger ##
				if (set.opt_triggers == true) {
					if (trigtrial[2] == 1) {
						trigger(trig.trialtypeDelay[trialtype[trialcount]]);
						trigger(0);
						trigtrial[2] = 0;
					}
				}

				// ## draw ##
				if (set.debug == true) {
					for (size_t i = 0; i < set.setsize; i++) {
						window->draw(boxes[i]);
					}
				}
				
				window->draw(fixcross);
			}

			// #### memory probe ####
			else if (elapsed.asMilliseconds() > timing.cue + onset_jitter[trialcount] + timing.memory_array + timing.interval2 ) {
				// ## trigger ##
				if (set.opt_triggers == true) {
					if (trigtrial[3] == 1) {
						trigger(trig.probe[probefidelity_cued[trialcount]]);
						trigger(0);
						trigtrial[3] = 0;
					}
				}

				// ## start RT clock ##
				if (epochstart == true) {
					RT = RTclock.restart();
					epochstart = false;
				}

				// ## draw ##
				if (set.debug == true) {
					for (size_t i = 0; i < set.setsize; i++) {
						window->draw(boxes[i]);
					}
				}
				
				window->draw(fixcross);

				switch (cuetype_all[trialcount]) {
				case 0: //global
					window->draw(boxes_fixedleft[left_probeorder[trialcount]]);
					window->draw(boxes_fixedright[right_probeorder[trialcount]]);
					break;
				case 1:
					window->draw(LocalCueboxes[0]);
					window->draw(LocalCueboxes[1]);
					break;
				}

				// ## if a response hasn't been made yet, check responses ##
				if (noresponse == true) {
					// ## response - target absent ##
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
					{
						// # get RT #
						RT = RTclock.getElapsedTime();
						RTvec[trialcount] = float(RT.asMilliseconds());

						// # update Bdata #
						respones[trialcount] = 0;

						// # display result #
						if (respones[trialcount] == probefidelity_cued[trialcount]) {
							accuracyvec[trialcount] = 1;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green
							std::cout << "		Correct ";
						}
						else {
							accuracyvec[trialcount] = 0;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //red
							std::cout << "		Incorrect ";
						}

						std::cout << RTvec[trialcount] << "ms response: absent" << std::endl;

						noresponse = false; // stop checking for response
					}

					// ## response - target present ##
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
					{
						// # get RT #
						RT = RTclock.getElapsedTime();
						RTvec[trialcount] = float(RT.asMilliseconds());

						// # update Bdata #
						respones[trialcount] = 1;

						// # display result #
						if (respones[trialcount] == probefidelity_cued[trialcount]) {
							accuracyvec[trialcount] = 1;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green
							std::cout << "		Correct ";
						}
						else {
							accuracyvec[trialcount] = 0;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //red
							std::cout << "		Incorrect ";
						}

						std::cout << RTvec[trialcount] << "ms response: present" << std::endl;

						noresponse = false; // stop checking for response
					}
				}

			}

			// ## boundingboxes ## 
			/*window->draw(stim.stimspace_left);
			window->draw(stim.stimspace_right);*/

			// #### Prepare for New Trial ####
			if (noresponse == false) {//(elapsed.asMilliseconds() > timing.trial) {

				// ## renew triggers ##
				if (set.opt_triggers == true) {
					std::vector<int> trigtrial = { 1, 1, 1,1 };
				}

				// ## save responses ##
				response_file.open(responseFileName, std::ios_base::app);
				response_file << trialcount << '\t' << int(respones[trialcount]) << '\t' << RTvec[trialcount] << '\t' << accuracyvec[trialcount] << std::endl;
				response_file.close();

				// ## reset variables ##
				clock2.restart();
				trialcount++;
				noresponse = true;
				epochstart = true;

				// ## periodically have a rest
				if (std::any_of(blocktrials.begin(), blocktrials.end(), [trialcount](int i) {return i == trialcount; })) {
					blockcount++;
					period = trialperiod::rest;
				}


				// ## close window if we've reached the end ##
				if (trialcount == set.numtrials_total) {
					std::cout << "close" << std::endl;
					window->close();
				}
				else {
					// ## prepare for next trial ##
					boxes = stim.shuffleboxes(boxes, all_coordinates, trialcount, all_colours); // shuffle box positions
					if (cuetype_all[trialcount] == 1) {
						LocalCueboxes = stim.makeLocalCueboxes(left_probeorder, right_probeorder, all_coordinates, trialcount);
					}

					const char* probetype = "";
					switch (cuetype_all[trialcount]) {
					case 0: probetype = "global"; break;
					case 1: probetype = "local"; break;
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					std::cout << std::endl;
					std::cout << "Trial: " << trialcount + 1 << " Arraytype: " << trialtype[trialcount] << " probetype: " << probetype << std::endl; // display where we are

					// ## display metadata
					const char* dir = "";

					const char* probefid = "";
					switch (cuedside[trialcount]) {
					case 1: dir = "Left"; break;
					case 2: dir = "Right"; break;
					}
					
					switch (probefidelity_cued[trialcount]) {
					case 0: probefid = "absent"; break;
					case 1: probefid = "present"; break;
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
					std::cout << "	Cue Direction: " << dir << 
								 "	Target: " << probefid << std::endl; // display some data

					
				}

			}
			break;
			}

			// ## display ##
			window->display();
		}
	}

	//record
	//framerate[framecount] = refresh.asMicroseconds();
	//framecount++;
	//if (framecount > f.trial - 1) {
	//	framecount = 1;
	//}
