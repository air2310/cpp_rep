#include <Windows.h>
#include <gdiplus.h>
#include <chrono>	//time
#include <thread> //sleep
#include <vector>

#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

VOID cue(HDC hdc, HWND hWnd, int nWidth, int nShip, int nHeight, int xxtra, int border, std::vector<Row>& ColorCond, int Trial, std::vector<int> Order)
{

	Gdiplus::Graphics gr(hdc);

	Font font(&FontFamily(L"Lucida Console"), 40);

	SolidBrush redBrush(Color(255, 255, 0, 0));
	SolidBrush greenBrush(Color(255, 0, 255, 0));
	SolidBrush blueBrush(Color(255, 0, 0, 255));
	SolidBrush whiteBrush(Color(255, 255, 255, 255));
	SolidBrush blackBrush(Color(255, 0, 0, 0));
	Color blackColor(255, 0, 0, 0);

	// Get Images
	Image positive(L"stim/stim_feedback_positive.png");
	Image negative(L"stim/stim_feedback_negative.png");
	Image field(L"stim/test_positions2.bmp");

	Rect fieldpos(0, 0, 1024, 1280);
	Rect destpos((nWidth / 2) + nShip / 4, nHeight / 2 - 50 - nShip / 4, nShip / 2, nShip / 2);  // Create a Rect object that specifies the destination 
	Rect destposR((nWidth / 2), nHeight / 2 - 50 - 35.5, nShip, nShip);  // Create a Rect object that specifies the destination of the image.
	Rect destneg((nWidth / 2) + nShip / 4, nHeight / 2 + 50 - nShip / 4, nShip / 2, nShip / 2);
	Rect destnegR((nWidth / 2), nHeight / 2 + 50 - 35.5, nShip, nShip);  // Create a Rect object that specifies the destination of the image.

																		 //gr.DrawImage(&field, fieldpos); // Draw the image.
	gr.FillRectangle(&whiteBrush, xxtra, 0, nHeight, nHeight);
	gr.FillRectangle(&blackBrush, (xxtra + border), border, (nHeight - 2 * border), (nHeight - 2 * border));

	gr.DrawString(L"HEALTH", -1, &font, PointF((nWidth / 2) - 300, nHeight / 2 - 75), &whiteBrush);
	gr.DrawString(L"DAMAGE", -1, &font, PointF((nWidth / 2) - 300, nHeight / 2 + 25), &whiteBrush);

	int condition = Order[Trial];
	switch (ColorCond[condition][0]) {
	case 1: {
		gr.FillRectangle(&redBrush, destposR);
		break; }// Draw the rectangle that bounds the image.
			
	case 2: {
		gr.FillRectangle(&greenBrush, destposR); 
		break; }
			
	case 3: {
		gr.FillRectangle(&blueBrush, destposR); 
		break; }
			
	}

	switch (ColorCond[condition][1]) {
	case 1: {
		gr.FillRectangle(&redBrush, destnegR);
		break; }// Draw the rectangle that bounds the image.

	case 2: {
		gr.FillRectangle(&greenBrush, destnegR);
		break; }

	case 3: {
		gr.FillRectangle(&blueBrush, destnegR);
		break; }

	}

	gr.DrawImage(&positive, destpos); // Draw the image.
	gr.DrawImage(&negative, destneg); // Draw the image.


	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	InvalidateRect(hWnd, NULL, TRUE);
	gr.Clear(blackColor);
}
