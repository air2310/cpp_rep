#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class flicktype { smooth, smoothsingle, smoothnoalph, blink
};

typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

double pi = 3.1415926535;

class flicker {
public:


	Matrix flickrates(int ftrial, std::vector<double> Hz, int numsquares, flicktype flick2use, double alphalevel, int refreshrate) {
		Matrix FLICKS(numsquares, Row(ftrial));

		for (int FF = 0; FF < numsquares; FF++) {
			switch (flick2use) {
			case flicktype::blink:
				FLICKS[FF] = blinkflick(ftrial, Hz[FF]);
				break;
			case flicktype::smooth:
				FLICKS[FF] = smoothflick(ftrial, Hz[FF], alphalevel, refreshrate);
				break;
			}

		}
		return FLICKS;
	};


private:

	std::vector<double> blinkflick(double ftrial, double Hz) {
		int numon = ftrial / Hz;
		std::vector<int> idx(numon + 1);
		std::vector<double> flick(ftrial);

		int IDX = 0; // where does the flicker turn on and off
		for (int i = 0; i < numon + 1; i++)
		{
			idx[i] = IDX;
			IDX += Hz;
		}

		int change = 0;
		int count = 0;
		for (int f = 0; f < ftrial; f++) //which frames are on and off
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

	std::vector<double> smoothflick(double ftrial, double Hz, double alphalevel, int refreshrate) {
		//int numon = ftrial / Hz;
		//std::vector<int> idx(numon + 1);
		//std::vector<int> flick(ftrial);

		//int IDX = 0;
		//for (int i = 0; i < numon + 1; i++)
		//{
		//	idx[i] = IDX;
		//	IDX += Hz;
		//}


		std::vector<double> wave = SIN(Hz, alphalevel,  ftrial, refreshrate);

	/*	int IDX2 = 0;
		int count = 0;
		for (int f = 0; f < ftrial; f++)
		{
			if (f == idx[count]) {
				if (count < numon) {
					count += 1;
				}
				IDX2 = 0;
			}

			flick[f] = wave[IDX2];
			IDX2 += 1;
		}*/
		return wave;
	}

	std::vector<double> SIN(double Hz, double alphalevel, int ftrial, int  refreshrate) {
		std::vector<double> wave(ftrial);

		double frames = refreshrate / Hz;

		double a = alphalevel / 2;
		for (double x = 0; x < ftrial; x++) {
			wave[x] = a*sin(2*pi/frames*x)+a ;
			//std::cout << wave[x] << ';';
		}
		/*double Hz = Hz-1 ; */
		//std::cout << std::endl;
		return wave;
	}

};

