#pragma once
#include <vector>

enum class gamesegments { rest, cue, flick };
enum class Freqrange { real, imag };

bool gamestarter(bool startgame, int framecount);

std::vector<double> makeclut(const char* filename);