//#include "C:\Program Files\MATLAB\R2015a\extern\include\mat.h"
//#include <Windows.h>
//#include <vector>
//
//int matcreate(char* file, std::vector<double> variable, int varsize, char* varname) {
//
//	MATFile *pmat;
//	mxArray *pa1;
//
//	pmat = matOpen(file, "w");
//
//	pa1 = mxCreateDoubleMatrix(varsize, 1, mxREAL);
//
//	memcpy((void *)mxGetPr(pa1), variable.data(), varsize*sizeof(double));
//	int status = matPutVariable(pmat, varname, pa1);
//
//	mxDestroyArray(pa1);
//	matClose(pmat);
//
//	return 0;
//}