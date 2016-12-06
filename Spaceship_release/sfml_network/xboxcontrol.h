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


GamePadXbox::GamePadXbox(int playerNumber)
{
	_controllerNum = playerNumber - 1; // Set the Controller Number
}


XINPUT_STATE GamePadXbox::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool GamePadXbox::is_connected()
{
	// clean the state
	memset(&_controllerState, 0, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if (Result == ERROR_SUCCESS)	return true;
	else return false;
}



void GamePadXbox::vibrate(int leftVal, int rightVal) //1-on 0-off
{
	// Create a new Vibraton 
	XINPUT_VIBRATION Vibration;

	memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

	int leftVib = (int)(leftVal * 65535);
	int rightVib = (int)(rightVal * 65535);

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVib;
	Vibration.wRightMotorSpeed = rightVib;
	// Vibrate the controller
	XInputSetState((int)_controllerNum, &Vibration);
}