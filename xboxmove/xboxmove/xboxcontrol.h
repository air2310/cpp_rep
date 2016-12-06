#pragma once
#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput9_1_0.lib")

class GamePadXbox
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
public:
	GamePadXbox(int playerNumber);
	XINPUT_STATE GetState();
	bool is_connected();
	void vibrate(int leftVal = 0, int rightVal = 0);
	//void update();

};

#endif

#include <vector>

int matcreate(char* file, std::vector<double> variable, int varsize, char* varname);