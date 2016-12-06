#include <vector>
#include <algorithm>


typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;


Row Createflicktimes(int nFrames, int Freq) {
	Row flicktimes(nFrames/2);
	int Count = 0;
	int Count2 = 0;
	for (int F = 0; F < nFrames/(Freq*2); F++) {
		for (int FF = 0; FF < Freq; FF++) {
			flicktimes[Count2] = Count*Freq*2+FF;
			Count2 = Count2 + 1;
		}
		Count = Count + 1;
	}
	return flicktimes;
}

//Frequency conditions
Matrix CreateFlicker(int nFrames, int nFreqs, std::vector<int> Freqs, int Refresh) {
	Matrix Flicker(nFreqs, Row(nFrames));

	
	for (int FF = 0; FF < nFreqs; FF++) {
		int Hz = Freqs[FF];
		double dHz = Refresh /Hz;

		Row flicktimes = Createflicktimes(nFrames, dHz);

		for (int F = 0; F < nFrames; F++) {
			
			if (std::find(flicktimes.begin(), flicktimes.end(), F) != flicktimes.end()) {
				Flicker[FF][F] = 1;
			}
			else {
				Flicker[FF][F] = 0;
			}
		}
	}

	return Flicker;
}


