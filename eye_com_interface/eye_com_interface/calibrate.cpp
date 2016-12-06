#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>  
#include "iViewXAPI.h"

char c = ' ';
int ret_calibrate = 0, ret_validate = 0;

void calibrate(CalibrationStruct calibrationData, AccuracyStruct accuracyData) {
	// shall we perform a calibration?
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	std::cout << "Do you want to calibrate? (y)es | (n)o" << std::endl;
	c = getchar();

	//flush the buffer
	getchar();

	if (c == 'y')
	{
		iV_SetupCalibration(&calibrationData);

		//StartCalibration();
		ret_calibrate = iV_Calibrate();

		switch (ret_calibrate)
		{
		case RET_SUCCESS:
			std::cout << "Calibration done successfully" << std::endl;

			// start validation
			ret_validate = iV_Validate();

			// show accuracy only if validation was successful
			if (ret_validate == RET_SUCCESS)
			{
				std::cout << "iV_GetAccuracy: " << iV_GetAccuracy(&accuracyData, 0) << std::endl;
				std::cout << "AccuracyData DevX: " << accuracyData.deviationLX << " DevY: " << accuracyData.deviationLY << std::endl;
				//getchar();
			}
			break;
		case ERR_NOT_CONNECTED:
			std::cout << "iViewX is not reachable" << std::endl;
			break;
		case ERR_WRONG_PARAMETER:
			std::cout << "Wrong Parameter used" << std::endl;
			break;
		case ERR_WRONG_DEVICE:
			std::cout << "Not possible to calibrate connected Eye Tracking System" << std::endl;
			break;
		default:
			std::cout << "An unknown error appeared" << std::endl;
			break;
		}
	}
}
