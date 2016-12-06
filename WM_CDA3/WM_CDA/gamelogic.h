#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <iostream>

//Cue type per block-->
//0 global 1 local

std::vector<int> create_cuetype_block() {
	std::srand(std::time(0));
	std::vector<int> cuetype_block(set.numblocks);

	for (size_t i = 0; i < set.numblocks; i++) {
		if (i < set.numblocks / 2) {
			cuetype_block[i] = 0;
		}
		else {
			cuetype_block[i] = 1;
		}
	}
	std::random_shuffle(cuetype_block.begin(), cuetype_block.end(), myrandom);

	return cuetype_block;
}

//Cue type across experiment-->
//0 global 1 local

std::vector<int> create_cuetype_all() {
	std::vector<int> cuetype_all(set.numtrials_total);
	std::vector<int> cuetype_withinblock(set.numtrials_block);

	std::vector<int> cuetype_block = create_cuetype_block();

	int count = 0;
	for (size_t i = 0; i < set.numblocks; i++) {
		for (size_t j = 0; j < set.numtrials_block; j++) {
			cuetype_all[count] = cuetype_block[i];
			count++;
		}

	}

	return cuetype_all;
}


// settype for each trial
// 1 = 4 colours, 2 = 2 colors, 3 = 3 unique colours

std::vector<int> create_trialtype(std::vector<int> cuetype_all) {
	//create vector of trialtypes
	std::vector<int> trialtype_tmp(set.numtrials_total/2);

	for (size_t i = 0; i < set.numtrials_total/2; i++){
		if (i < set.numtrials_persetsize) {
			trialtype_tmp[i] = 1;
		}
		else if ((i > set.numtrials_persetsize - 1) & (i < set.numtrials_persetsize * 2) ){
			trialtype_tmp[i] = 2;
		}
		else {
			trialtype_tmp[i] = 3;
		}
	}

	std::vector<int> trialtype_tmp2 = trialtype_tmp;
	std::random_shuffle(trialtype_tmp.begin(), trialtype_tmp.end(), myrandom);
	std::random_shuffle(trialtype_tmp2.begin(), trialtype_tmp2.end(), myrandom);

	//split evenly across cuetype

	std::vector<int> trialtype(set.numtrials_total);

	int count_global = 0;
	int count_local = 0;
	for (size_t i = 0; i < set.numtrials_total; i++) {
		switch (cuetype_all[i]) {
		case 0: //global
			trialtype[i] = trialtype_tmp[count_global];
			count_global++;
			break;

		case 1: //local
			trialtype[i] = trialtype_tmp[count_local];
			count_local++;
			/*if (count_local == 480) {
				int a;
			}*/
			break;
		}
	}

	return trialtype;
}

//Cuedside - within set -->
//1 left 2 right

std::vector<int> create_cuedside_set() { 
	std::vector<int> cuedside_set(set.numtrials_persetsize);

	for (size_t i = 0; i < set.numtrials_persetsize; i++) {
		if (i < set.numtrials_persetsize / 2) {
			cuedside_set[i] = 1;
		}
		else {
			cuedside_set[i] = 2;
		}
	}
	std::random_shuffle(cuedside_set.begin(), cuedside_set.end(), myrandom);

	return cuedside_set; 
}


//Cuedside - for whole experiment --> 
//50% left, 50% right. counterbalanced to that 50% left and right for each condition (onecol, 4identicalcols, 4uniquecols);
//1 left 2 right

std::vector<int> create_cuedside_all(std::vector<int> trialtype, std::vector<int> cuetype_all) {
	std::vector<int> cuedside_all(set.numtrials_total);

	std::vector<int> cuedside_set1_global = create_cuedside_set();
	std::vector<int> cuedside_set2_global = create_cuedside_set();
	std::vector<int> cuedside_set3_global = create_cuedside_set();

	std::vector<int> cuedside_set1_local = create_cuedside_set();
	std::vector<int> cuedside_set2_local = create_cuedside_set();
	std::vector<int> cuedside_set3_local = create_cuedside_set();

	int count1 = 0; 	int count1a = 0;
	int count2 = 0;		int count2a = 0;
	int count3 = 0;		int count3a = 0;
	for (size_t i = 0; i < set.numtrials_total; i++) {
		switch (cuetype_all[i]) {
		case 0: // global
			switch (trialtype[i]) {
			case 1: //four identical colours
				cuedside_all[i] = cuedside_set1_global[count1];
				count1++;
				break;

			case 2: //twocols colour
				cuedside_all[i] = cuedside_set2_global[count2];
				count2++;
				break;

			case 3: //four unique colours
				cuedside_all[i] = cuedside_set3_global[count3];
				count3++;
				break;
			}
			break;

		case 1: // local
			switch (trialtype[i]) {
			case 1: //four identical colours
				cuedside_all[i] = cuedside_set1_local[count1a];
				count1a++;
				break;

			case 2: //twocols colour
				cuedside_all[i] = cuedside_set2_local[count2a];
				count2a++;
				break;

			case 3: //four unique colours
				cuedside_all[i] = cuedside_set3_local[count3a];
				count3a++;
				break;
			}
			break;
		}

	}

	return cuedside_all;
}


//Probe fidelity - 50% of probes were really there, 50% were on the other side -->
//Counterbalanced rather than fully random, 50%correct for each condition (4identicalcols, 2 cols, 4uniquecols) and each direction (left, right)
//0 - probed item was absent on cued side; 1 - probed item was present on cued side

std::vector<int> create_probefidelity_set() {
	std::vector<int> probefidelity_set(set.numtrials_persetsize/2);

	for (size_t i = 0; i < set.numtrials_persetsize/2; i++) {
		if (i < set.numtrials_persetsize / 4) {
			probefidelity_set[i] = 0;
		}
		else {
			probefidelity_set[i] = 1;
		}
	}
	std::random_shuffle(probefidelity_set.begin(), probefidelity_set.end(), myrandom);

	return probefidelity_set;
}

//Probe fidelity whole exp- 50% of probes were really there, 50% were on the other side -->
//Counterbalanced rather than fully random, 50%correct for each condition (onecol, 4identicalcols, 4uniquecols) and each direction (left, right)
//0 - probed item was absent on cued side; 1 - probed item was present on cued side

std::vector<int> create_probefidelity_all(std::vector<int> trialtype, std::vector<int> cuedside, std::vector<int> cuetype_all) {
	std::vector<int> probefidelity_all(set.numtrials_total);

	std::vector<std::vector<int>> probefid_set(12, std::vector<int>(set.numtrials_persetsize / 2));
	std::vector<int> counts(12);
	for (size_t i = 0; i < 12; i++) {
		probefid_set[i] = create_probefidelity_set();
		counts[i] = 0;
	}

	int ii =0;
	for (size_t i = 0; i < set.numtrials_total; i++) {
		switch (cuetype_all[i]) {
		case 0:
			switch (trialtype[i]) {
			case 1: //four identical colours
				switch (cuedside[i]) {
				case 1: ii = 0; break;//left
				case 2: ii = 1; break;//right
				}; 	break;

			case 2: //two colours
				switch (cuedside[i]) {
				case 1: ii = 2; break;//left
				case 2: ii = 3; break;//right
				};	break;

			case 3: //four unique colours
				switch (cuedside[i]) {
				case 1: ii = 4; break;//left
				case 2: ii = 5; break;//right
				};	break;
			}
			break;
		case 1:
			switch (trialtype[i]) {
			case 1: //four identical colours
				switch (cuedside[i]) {
				case 1: ii = 6; break;//left
				case 2: ii = 7; break;//right
				}; 	break;

			case 2: //two colours
				switch (cuedside[i]) {
				case 1: ii = 8; break;//left
				case 2: ii = 9; break;//right
				};	break;

			case 3: //four unique colours
				switch (cuedside[i]) {
				case 1: ii = 10; break;//left
				case 2: ii = 11; break;//right
				};	break;
			}
			break;
		}
		probefidelity_all[i] = probefid_set[ii][counts[ii]];
		//std::cout << ii << " " << counts[ii] << std::endl;
		counts[ii]++;

	}

	return probefidelity_all;
}

//Probe Order - what colours are we actually probing when?

std::vector<int> create_probeorder(std::vector<int> cuedside, std::vector<int> probefidelity_cued, 
	std::vector<int> probefidelity_uncued,  int side, std::vector<std::vector<int>> all_colours, std::vector<int> cuetype_all) {

	std::vector<int> probeorder(set.numtrials_total);
	std::vector<int> coloptions(set.setsize);
	std::vector<int> coloptions_left(set.setsize/2);
	std::vector<int> coloptions_right(set.setsize / 2);

	std::uniform_int_distribution<> distLeft(0, 3); //choose from the left
	std::uniform_int_distribution<> distRight(4, 7); //choose from the right
	std::uniform_int_distribution<> distAll(0, 6); //choose from the right

	float tmpcol;
	bool proceed;

	for (size_t i = 0; i < set.numtrials_total; i++) {
		coloptions = all_colours[i];
		coloptions_left = { coloptions[0], coloptions[1], coloptions[2], coloptions[3] };
		coloptions_right = { coloptions[4], coloptions[5], coloptions[6], coloptions[7] };

		if (side == cuedside[i]) { //cued side
			if (probefidelity_cued[i] == 1) { //colour was present
				switch (side) { 
				case 1: //left
					switch (cuetype_all[i]) { 
					case 0: //global
						probeorder[i] = coloptions[distLeft(rng)]; //choose a rand colour from left
						break;
					case 1: //local
						probeorder[i] = coloptions_left[0]; //choose specific colour from left
						break;
					}
					break;

				case 2: //right
					switch (cuetype_all[i]) {
					case 0: //global
						probeorder[i] = coloptions[distRight(rng)]; //choose a rand colour from left
						break;
					case 1: //local
						probeorder[i] = coloptions_right[0]; //choose specific colour from left
						break;
					}
					break;
				}
				
			}
			else { //colour was absent
				switch (side) {
				case 1: //left
					proceed = false;
					while (proceed == false) { //make sure you're not picking a colour from the left distribution
						tmpcol = float(distAll(rng));

						if (cuetype_all[i] == 1) { //local
							if ((tmpcol != coloptions_left[0]) ) {
								proceed = true;
							}
						}
						else { //global
							if ((tmpcol != coloptions_left[0]) & (tmpcol != coloptions_left[1]) &
								(tmpcol != coloptions_left[2]) & (tmpcol != coloptions_left[3])) {
								proceed = true;
							}
						}
					}

					probeorder[i] = int(tmpcol);
					break;

				case 2: //right
					proceed = false;
					while (proceed == false) {  //make sure you're not picking a colour from the right distribution
						tmpcol = float(distAll(rng));

						if (cuetype_all[i] == 1) { //local
							if ((tmpcol != coloptions_right[0])) {
								proceed = true;
							}
						}
						else { //global
							if ((tmpcol != coloptions_right[0]) & (tmpcol != coloptions_right[1]) &
								(tmpcol != coloptions_right[2]) & (tmpcol != coloptions_right[3])) {
								proceed = true;
							}
						}
					}

					probeorder[i] = int(tmpcol); //choose a rand colour from right
					break;
				}
			}
		}
		else { //uncued side
			if (probefidelity_uncued[i] == 1) { //colour was present
				switch (side) {
				case 1: //left
					switch (cuetype_all[i]) {
					case 0: //global
						probeorder[i] = coloptions[distLeft(rng)]; //choose a rand colour from left
						break;
					case 1: //local
						probeorder[i] = coloptions_left[0]; //choose specific colour from left
						break;
					}
					break;

				case 2: //right
					switch (cuetype_all[i]) {
					case 0: //global
						probeorder[i] = coloptions[distRight(rng)]; //choose a rand colour from left
						break;
					case 1: //local
						probeorder[i] =coloptions_right[0]; //choose specific colour from left
						break;
					}
					break;
				}

			}
			else { //colour was absent
				switch (side) {
				case 1: //left
					proceed = false;
					while (proceed == false) {  //make sure you're not picking a colour from the right distribution
						tmpcol = float(distAll(rng));

						if (cuetype_all[i] == 1) { //local
							if ((tmpcol != coloptions_left[0])) {
								proceed = true;
							}
						}
						else { //global
							if ((tmpcol != coloptions_left[0]) & (tmpcol != coloptions_left[1]) &
								(tmpcol != coloptions_left[2]) & (tmpcol != coloptions_left[3])) {
								proceed = true;
							}
						}
					}

					probeorder[i] = int(tmpcol); //choose a rand colour from right
					break;
				case 2: //right
					proceed = false;
					while (proceed == false) {  //make sure you're not picking a colour from the right distribution
						tmpcol = float(distAll(rng));

						if (cuetype_all[i] == 1) { //local
							if ((tmpcol != coloptions_right[0]) ) {
								proceed = true;
							}
						}
						else { // global
							if ((tmpcol != coloptions_right[0]) & (tmpcol != coloptions_right[1]) &
								(tmpcol != coloptions_right[2]) & (tmpcol != coloptions_right[3])) {
								proceed = true;
							}
						}
					}

					probeorder[i] = int(tmpcol); //choose a rand colour from right
					break;
				}
			}
		}

	}
	return probeorder;
}


//Create array containing first trial in each block

std::vector<int> create_blocktrials() {
	std::vector<int> blocktrials(set.numblocks);

	for (size_t i = 0; i < set.numblocks; i++) {
		blocktrials[i] = int(i*set.numtrials_block);
	}

	return blocktrials;
}


//vector for storing responses --> 0 = absent, 1 = present, -1 = noresponse
std::vector<int> create_responses() { 
	std::vector<int> responses(set.numtrials_total);

	for (size_t i = 0; i < set.numtrials_total; i++) {
		responses[i] = -1;
	}
	return responses;
}

//vector to store Reactiontime
std::vector<float> create_RTvec() { 
	std::vector<float> RTvec(set.numtrials_total);

	for (size_t i = 0; i < set.numtrials_total; i++) {
		RTvec[i] = -1;
	}
	return RTvec;
}

//vector to store Accuracy ->  -1 = no answer, 0 = incorrect, 1 = correct,
std::vector<float> create_accuracyvec() {
	std::vector<float> accuracyvec(set.numtrials_total);

	for (size_t i = 0; i < set.numtrials_total; i++) {
		accuracyvec[i] = -1;
	}
	return accuracyvec;
}

// jitter onset

std::vector<int> create_onset_jitter() {
	std::vector<int> jitter(set.numtrials_total);

	std::uniform_int_distribution<> dist_jitter(timing.interval1_min, timing.interval1_max); //choose from the left

	for (size_t i = 0; i < set.numtrials_total; i++) {
		jitter[i] = dist_jitter(rng);
	}

	return jitter;

}