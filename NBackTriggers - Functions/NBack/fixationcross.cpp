//fixationcross.cpp
#include <Windows.h> 
#include <ctime>        // std::time
#include <thread>
#include <chrono>		//time
#include <gdiplus.h>
#include "fixationcross.h"

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


void fixationcross(HDC hdc, HWND hWnd, int Xx, int Xy, int Xwidth, int Xheight)
{
	Graphics graphics(hdc);

	SolidBrush whiteBrush(Color(255, 255, 255, 255));
	Color blackColor(255, 0, 0, 0);


	graphics.FillRectangle(&whiteBrush, Xx, Xy, Xwidth, Xheight); //Fixation Cross
	graphics.FillRectangle(&whiteBrush, Xx + 20, Xy - 20, Xheight, Xwidth);
	InvalidateRect(hWnd, NULL, TRUE);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	graphics.Clear(blackColor);
}
