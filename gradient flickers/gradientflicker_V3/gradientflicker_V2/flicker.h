#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class flicktype { blink, smooth };

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

double pi = 3.1415926535;

class flicker {
public:


	Matrix flickrates(int flicktime, std::vector<int> Hzcount, int numsquares, flicktype flick2use, double alphalevel) {
		Matrix FLICKS(numsquares, Row(flicktime));

		for (int FF = 0; FF < numsquares; FF++) {
			switch (flick2use) {
			case flicktype::blink:
				FLICKS[FF] = blinkflick(flicktime, Hzcount[FF]);
				break;
			case flicktype::smooth:
				FLICKS[FF] = smoothflick(flicktime, Hzcount[FF], alphalevel);
				break;
			}

		}
		return FLICKS;
	};


private:

	std::vector<int> blinkflick(double flicktime, double Hzcount) {
		int numon = flicktime / Hzcount;
		std::vector<int> idx(numon + 1);
		std::vector<int> flick(flicktime);

		int IDX = 0; // where does the flicker turn on and off
		for (int i = 0; i < numon + 1; i++)
		{
			idx[i] = IDX;
			IDX += Hzcount;
		}

		int change = 0;
		int count = 0;
		for (int f = 0; f < flicktime; f++) //which frames are on and off
		{
			if (f == idx[count]) {
				if (count < numon) {
					count += 1;
				}

				if (change == 0) { change = 1; }
				else if (change == 1) { change = 0; }
			}
			flick[f] = change;
		}
		return flick;
	}

	std::vector<int> smoothflick(double flicktime, double Hzcount, double alphalevel) {
		int numon = flicktime / Hzcount;
		std::vector<int> idx(numon + 1);
		std::vector<int> flick(flicktime);

		int IDX = 0;
		for (int i = 0; i < numon + 1; i++)
		{
			idx[i] = IDX;
			IDX += Hzcount;
		}


		std::vector<double> wave = SIN(Hzcount, alphalevel);

		int IDX2 = 0;
		int count = 0;
		for (int f = 0; f < flicktime; f++)
		{
			if (f == idx[count]) {
				if (count < numon) {
					count += 1;
				}
				IDX2 = 0;
			}

			flick[f] = wave[IDX2];
			IDX2 += 1;
		}
		return flick;
	}

	std::vector<double> SIN(double Hzcount, double alphalevel) {
		std::vector<double> wave(Hzcount);

		double a = alphalevel / 2;
		double Hz = Hzcount-1 ; 
		for (int x = 0; x < Hzcount; x++) {
			wave[x] = a*sin(2*pi*(1/Hz)*x)+a ;
			std::cout << wave[x] << ';';
		}
		std::cout << std::endl;
		return wave;
	}

};

