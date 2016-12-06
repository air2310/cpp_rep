#include <Windows.h>
#include <gdiplus.h>
#include <chrono>	//time
#include <thread> //sleep
#include <vector>

#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;



int Trial(HDC hdc, HWND hWnd, int nWidth, int nShip, int nHeight, int xxtra, int border, int flicktime, int nFrames, int nAst, std::vector<Row> AstX, std::vector<Row> AstY)
{
	int points = 0;
	ShowCursor(FALSE);//hides the cursor
	Graphics graphics(hdc);

	Font font(&FontFamily(L"Lucida Console"), 40);

	SolidBrush redBrush(Color(255, 255, 0, 0));
	SolidBrush greenBrush(Color(255, 0, 255, 0));
	SolidBrush blueBrush(Color(255, 0, 0, 255));
	SolidBrush yellowBrush(Color(255, 255, 255, 0));
	SolidBrush whiteBrush(Color(255, 255, 255, 255));
	SolidBrush blackBrush(Color(255, 0, 0, 0));
	SolidBrush greyBrush(Color(255, 150, 150, 150));
	Color blackColor(255, 0, 0, 0);

	// Get Images
	Image positive(L"stim/stim_feedback_positive.png");
	Image negative(L"stim/stim_feedback_negative.png");
	Image field(L"stim/test_positions2.bmp");



	for (int F = 0; F < nFrames; F++) {
		graphics.FillRectangle(&whiteBrush, xxtra, 0, nHeight, nHeight);
		graphics.FillRectangle(&blackBrush, (xxtra + border), border, (nHeight - 2 * border), (nHeight - 2 * border));
		//Rect fieldpos(0, 0, nHeight, 1280);
		//graphics.DrawImage(&field, fieldpos); // Draw the image.

		POINT p;
		if (GetCursorPos(&p)) //cursor position now in p.x and p.y
		{
		}

		graphics.FillRectangle(&whiteBrush, p.x - nShip / 2, p.y - nShip / 2, nShip, nShip);

		for (int A = 0; A < nAst; A++) {
			double xmin = AstX[A][F] + xxtra - nShip / 2;
			double xmax = AstX[A][F] + xxtra + 1.5*nShip;
			double ymin = AstY[nAst - 1 - A][F] - nShip / 2;
			double ymax = AstY[nAst - 1 - A][F] + 1.5*nShip;

			if (A < (nAst / 3)) {
				graphics.FillRectangle(&redBrush, AstX[A][F] + xxtra, AstY[nAst - 1 - A][F], nShip, nShip);

				if (p.x > xmin && p.x < xmax  && p.y > ymin && p.y < ymax) {
					graphics.FillRectangle(&yellowBrush, p.x - nShip / 2, p.y - nShip / 2, nShip, nShip);
					++points;
				}
			}
			else if (A < ((nAst / 3) * 2)) {
				graphics.FillRectangle(&greenBrush, AstX[A][F] + xxtra, AstY[nAst - 1 - A][F], nShip, nShip);

				if (p.x > xmin && p.x < xmax  && p.y > ymin && p.y < ymax) {
					graphics.FillRectangle(&greyBrush, p.x - nShip / 2, p.y - nShip / 2, nShip, nShip);
					//Rect destpos(p.x+nShip/2, p.y+nShip/2, nShip/2, nShip/2);  // Create a Rect object that specifies the destination of the image.
					//graphics.DrawImage(&positive, destpos); // Draw the image.
					--points;
				}
			}
			else {
				graphics.FillRectangle(&blueBrush, AstX[A][F] + xxtra, AstY[nAst - 1 - A][F], nShip, nShip);
			}

		}

		std::this_thread::sleep_for(std::chrono::microseconds(flicktime));
		InvalidateRect(hWnd, NULL, TRUE);
		graphics.Clear(blackColor);
	}
	ShowCursor(TRUE);//shows it again
	return points;
}