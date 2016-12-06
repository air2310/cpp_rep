#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>  
#include "iViewXAPI.h"
#include "Serial.h"
#include "stdafx.h"


//Data Settings

char* direct_data = "C:\\Users\\SLRC_admin\\Desktop\\Experiments\\Cooperation\\eyedata\\";

const char* filetype = ".idf";
char* uscore = "_";

//char* measure = "EEG"; // "fNIRS"; //fNIRS or eeg
char* session = "Pilot2"; //which session of fNIRS or EEG are you up to?
char* ID = "2"; //participant ID
char* side = "Right"; //left or right


// Serial Port Settings%

int nPort = 1;
int nBaud = 9600;

char b = ' ';

char* makefilename() {

	char* str = new char[70];
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);

	localtime_s(&timeinfo, &rawtime);

	strftime(str, 100, "%I-%M%p_%F", &timeinfo);

	//time_info.tm_hour

	char*  file2save = new char[1];
	
	size_t bufsize = 100;
	strcpy_s(file2save, bufsize, direct_data );
	//strcat_s(file2save, bufsize, measure);
	//strcat_s(file2save, bufsize, uscore);

	strcat_s(file2save, bufsize, session);
	strcat_s(file2save, bufsize, uscore);

	strcat_s(file2save, bufsize, ID);
	strcat_s(file2save, bufsize, uscore);

	strcat_s(file2save, bufsize, side);
	strcat_s(file2save, bufsize, uscore);
	strcat_s(file2save, bufsize, str);
	strcat_s(file2save, bufsize, filetype);

	
	return file2save;
}


int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


	//std::cout << "Measure: " << measure << std::endl;
	std::cout << "Session: " << session << std::endl;
	std::cout << "Participant ID: " << ID << std::endl;
	std::cout << "Side: " << side << std::endl;
	std::cout << std::endl;

	std::cout << "Is this information correct? (y)es | (n)o" << std::endl;
	b = getchar();
	getchar(); //flush the buffer

	if (b == 'n') {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		std::cout << "Well then exit and fix it!!!" << std::endl;
		getchar();
	}

	std::cout << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	AccuracyStruct accuracyData;
	SystemInfoStruct systemInfoData;
	CalibrationStruct calibrationData;
	int ret_connect1 ; 
	
	char repeat = ' ';

	std::cout << "Output from iViewXAPI Demo" << std::endl;

	// define logger 
	iV_SetLogger(1, "iViewXSDK_cpp_Demo.txt");

	std::cout << "Test iViewXAPI Demo" << std::endl;

	//connect to iViewX 
	ret_connect1 = iV_Connect("10.16.97.24", 0006, "10.16.97.24", 0006);
	//std::cout <<ret_connect1 << std::endl;

	switch (ret_connect1)
	{
	case RET_SUCCESS:
		std::cout << "connection was established successfully" << std::endl;

		// read out meta data from iViewX 
		std::cout << "GetSystemInfo: " << iV_GetSystemInfo(&systemInfoData) << std::endl;
		std::cout << "SystemInfo ETSystem: " << systemInfoData.iV_ETDevice << std::endl;
		std::cout << "SystemInfo iV_Version: " << systemInfoData.iV_MajorVersion << "." << systemInfoData.iV_MinorVersion << "." << systemInfoData.iV_Buildnumber << std::endl;
		std::cout << "SystemInfo API_Version: " << systemInfoData.API_MajorVersion << "." << systemInfoData.API_MinorVersion << "." << systemInfoData.API_Buildnumber << std::endl;
		std::cout << "SystemInfo samplerate: " << systemInfoData.samplerate << std::endl;

		break;
	case ERR_COULD_NOT_CONNECT:
		std::cout << "Connection could not be established" << std::endl;
		break;
	case ERR_WRONG_PARAMETER:
		std::cout << "Wrong Parameter used" << std::endl;
		break;
	default:
		std::cout << "Any other error appeared" << std::endl;
		return 0;
	}


	if (ret_connect1 == RET_SUCCESS)
	{
		// set up calibration
		calibrationData.method = 3;
		calibrationData.speed = 0;
		calibrationData.displayDevice = 1;
		calibrationData.targetShape = 2;
		calibrationData.foregroundBrightness = 250;
		calibrationData.backgroundBrightness = 230;
		calibrationData.autoAccept = 1;
		calibrationData.targetSize = 20;
		calibrationData.visualization = 1;
		strcpy_s(calibrationData.targetFilename, "");

		iV_GetAccuracy(&accuracyData, 0);

		std::cout << std::endl;

		calibrate(calibrationData, accuracyData);

		std::cout << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		 //show some windows
		/*iV_ShowEyeImageMonitor();
		iV_ShowTrackingMonitor();*/
		iV_ShowAccuracyMonitor();

		// Start recording

		iV_StartRecording();

		//Triggers

		CSerial serial;
		if (serial.Open(nPort, nBaud))
		{
			std::cout << "Port opened successfully" << std::endl;
			std::cout << "Hit 's' to stop and save" << std::endl;

			//int t1 = clock();
			while (1) { //int t2 = clock() - t1 < 60000
				char* lpBuffer = new char[500];
				int  trigger = serial.ReadData(lpBuffer, 500);
				delete[]lpBuffer;

				if (trigger > 0) {
					
					std::cout << trigger << std::endl;
					char eyetrig[4];	memset(eyetrig, '\0', sizeof(trigger));
					sprintf_s(eyetrig, "%d", trigger);


					iV_SendImageMessage(eyetrig);
					
				}
				

				if(GetAsyncKeyState(0x53)) {

					//Stop recording
					iV_StopRecording();

					std::cout << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

					std::cout << ("Eye tracking stopped!") << std::endl;

					//save data
					std::cout << ("Saving Data...") << std::endl;

					char*  file2save = makefilename();
					std::cout << file2save << std::endl;

					iV_SaveData(file2save, "", "", 1);

					// disconnect
					std::cout << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
					std::cout << "iV_Disconnect: " << iV_Disconnect() << std::endl;

					break;
				}

			}
		}
		else
		std::cout << ("Failed to open port!") << std::endl;

	}

	std::cout << ("Enter any key to exit") << std::endl;
	int Pause;
	std::cin >> Pause;
	//return 0;

}