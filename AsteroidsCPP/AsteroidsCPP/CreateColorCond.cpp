#include <vector>


typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

//
//std::vector<int> CreateColorconds4(int nCond) {
//	std::vector<int> Colorconds(nCond);
//	for (int C = 0; C < 6; C++) {
//		Colorconds[C] = C + 1;
//	}
//	return Colorconds;
//}


//Color conditions
Matrix CreateColorCond() {
	int nCond = 6;
	Matrix Colorcond(nCond, Row(3));
	
	Colorcond[0][0] = 1; Colorcond[0][1] = 2;  Colorcond[0][2] = 3;
	Colorcond[1][0] = 1; Colorcond[1][1] = 3;  Colorcond[1][2] = 2;
	Colorcond[2][0] = 2; Colorcond[2][1] = 1;  Colorcond[2][2] = 3;
	Colorcond[3][0] = 2; Colorcond[3][1] = 3;  Colorcond[3][2] = 1;
	Colorcond[4][0] = 3; Colorcond[4][1] = 1;  Colorcond[4][2] = 2;
	Colorcond[5][0] = 3; Colorcond[5][1] = 2;  Colorcond[5][2] = 1;

	//Colorcond[3] = CreateColorconds4(nCond);


	return Colorcond;
}
