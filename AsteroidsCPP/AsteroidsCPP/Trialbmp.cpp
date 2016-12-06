#include <Windows.h>
#include <gdiplus.h>
#include <chrono>	//time
#include <thread> //sleep
#include <vector>
#include <tchar.h>


//#pragma comment (lib,"Gdiplus.lib")
//using namespace Gdiplus;

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;



int Trial(HDC hdc, HWND hWnd, int nWidth, int nShip, int nHeight, int xxtra, int border, int flicktime, int nFrames, int nAst, std::vector<Row> AstX, std::vector<Row> AstY, std::vector<Row>& ColorCond, int Trial, std::vector<int> Order, std::vector<Row>& Flicker)
{
	Gdiplus::Graphics gr(hdc);
	
	int points = 0;
	int condition = Order[Trial];
	ShowCursor(FALSE);//hides the cursor
	
	// Create and draw onto memory bitmap
	
	LONG bmpWidth = 1280;
	LONG bmpHeight = 1024;
	//HBITMAP sprites = (HBITMAP)LoadImage(0, _T("green.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	for (int F = 0; F < nFrames; F++) {

		auto t1 = std::chrono::high_resolution_clock::now();

		HDC memDC = CreateCompatibleDC(NULL);
		HBITMAP bmp = CreateCompatibleBitmap(hdc, bmpWidth, bmpHeight);
		
		SelectObject(memDC, bmp);

		// Get Images
		//Bitmap positive(L"stim/stim_feedback_positive.png");
		//Image negative(L"stim/stim_feedback_negative.png");
		//Image field(L"stim/test_positions2.bmp");

		//HBITMAP sprites = (HBITMAP)LoadBitmap(NULL, MAKEINTRESOURCE(_T("green.bmp")));
		
		HPEN whitepen = CreatePen(2, 8, RGB(0xff, 0xff, 0xff));
		HPEN redpen = CreatePen(2, 8, RGB(0xff, 0,0));
		HPEN greenpen = CreatePen(2, 8, RGB(0, 0xff, 0));
		HPEN bluepen = CreatePen(2, 8, RGB(0, 0, 0xff));
		HBRUSH redbrush = CreateSolidBrush(RGB(0xff, 0, 0));
		HBRUSH greenbrush = CreateSolidBrush(RGB(0, 0xff, 0));
		HBRUSH bluebrush = CreateSolidBrush(RGB(0, 0, 0xff));
		HBRUSH whitebrush = CreateSolidBrush(RGB(0xff, 0xff, 0xff));
		HBRUSH blackbrush = CreateSolidBrush(TRANSPARENT);
		//HBRUSH greybrush = CreateSolidBrush(RGB(125, 125, 125));
		//HBRUSH yellowbrush = CreateSolidBrush(RGB(0xff, 0xff, 0));
		//HBRUSH  green =  CreatePatternBrush(sprites);
	
		HPEN nullpen = CreatePen(2, 4, RGB(0xff, 0xff, 0xff));
				
		//SetBkColor(memDC, GetStockObject(NULL_BRUSH));

		SelectObject(memDC,whitebrush);
		Rectangle(memDC, xxtra, 0, nHeight+xxtra, nHeight);
		

		SelectObject(memDC, blackbrush);
		Rectangle(memDC, (xxtra + border), border,xxtra + nHeight-border, nHeight -border);
		//DeleteObject(blackbrush);

		/*SelectObject(memDC, GetStockObject(NULL_BRUSH));
		Rectangle(memDC, p.x - nShip / 3, p.y - nShip / 3, p.x + nShip / 3, p.y + nShip / 3);*/
		

		for (int A = 0; A < nAst; A++) {
			double xmin = AstX[A][F] + xxtra - nShip / 2;
			double xmax = AstX[A][F] + xxtra + 1.5*nShip;
			double ymin = AstY[A][F] - nShip / 2;
			double ymax = AstY[A][F] + 1.5*nShip;

			if (A < (nAst / 3)) {

				//SelectObject(memDC, blackbrush);
				SelectObject(memDC, redpen);
				Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				if (Flicker[1][F] == 0) {
					SelectObject(memDC, blackbrush);
					Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);
					
					}
				else if (Flicker[1][F] == 1) {
					SelectObject(memDC, redbrush);
					Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);
				}
				

			}
			
			/*else if (A < ((nAst / 3) * 2) && A >= (nAst / 3)) {
				SelectObject(memDC, blackbrush);
				Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				SelectObject(memDC, greenpen);
				Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				if (Flicker[2][F] == 0) {
					SelectObject(memDC, blackbrush);
					Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				}
				else if (Flicker[2][F] == 1) {
					SelectObject(memDC, greenbrush);
					Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				}
				
			}*/
			else if (A >= ((nAst / 3) * 2)) {

				SelectObject(memDC, bluepen);
				Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				if (Flicker[3][F] == 0) {
					SelectObject(memDC, blackbrush);
					Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				}
				else if (Flicker[3][F] == 1) {
					SelectObject(memDC, bluebrush);
					Rectangle(memDC, AstX[A][F] + xxtra, AstY[A][F], AstX[A][F] + xxtra + nShip, AstY[A][F] + nShip);

				}
				
			}
		}


		POINT p;
		if (GetCursorPos(&p)) //cursor position now in p.x and p.y
		{
		}

		
		SelectObject(memDC, whitebrush);
		SelectObject(memDC, blackbrush);
		SelectObject(memDC,whitepen);
		

		RECT rect = { p.x - nShip / 2, p.y - nShip / 2, p.x + nShip / 2, p.y + nShip / 2 };
		Rectangle(memDC, rect.left, rect.top, rect.right, rect.bottom);
		
		for (int A = 0; A < nAst; A++) {
			double xmin = AstX[A][F] + xxtra - nShip / 2;
			double xmax = AstX[A][F] + xxtra + 1.5*nShip;
			double ymin = AstY[A][F] - nShip / 2;
			double ymax = AstY[A][F] + 1.5*nShip;

			RECT rect1 = {p.x - nShip / 4,
				p.y ,
				p.x + nShip / 4,
				p.y };
			RECT rect2 = { p.x,
				p.y - nShip / 4 ,
				p.x,
				p.y + nShip / 4 };

			SelectObject(memDC, nullpen);
			SelectObject(memDC, whitebrush);

			if (A < (nAst / 3)) {
				if (p.x > xmin && p.x < xmax  && p.y > ymin && p.y < ymax) {
					if (ColorCond[condition][0] == 1) {
						Rectangle(memDC, rect1.left, rect1.top - 2, rect1.right, rect1.bottom + 2);
						Rectangle(memDC, rect2.left - 2, rect2.top, rect2.right + 2, rect2.bottom);
						++points;
						break;
					}
					if (ColorCond[condition][1] == 1) {
						Rectangle(memDC, rect1.left, rect1.top - 2, rect1.right, rect1.bottom + 2);
						//Rectangle(memDC, rect2.left - 2, rect2.top, rect2.right + 2, rect2.bottom);
						--points;
						break;
					}
					break;
				}
			}
			//else if (A < ((nAst / 3) * 2) && A >= (nAst / 3)) {
			//	if (p.x > xmin && p.x < xmax  && p.y > ymin && p.y < ymax) {
			//		
			//		if (ColorCond[condition][0] == 2) {
			//			Rectangle(memDC, rect1.left, rect1.top - 2, rect1.right, rect1.bottom + 2);
			//			Rectangle(memDC, rect2.left - 2, rect2.top, rect2.right + 2, rect2.bottom);
			//			++points;
			//			break;
			//		}
			//		if (ColorCond[condition][1] == 2) {
			//			Rectangle(memDC, rect1.left, rect1.top - 2, rect1.right, rect1.bottom + 2);
			//			//Rectangle(memDC, rect2.left - 2, rect2.top, rect2.right + 2, rect2.bottom);
			//			--points;
			//			break;
			//		}
			//		break;
			//	}
			//}
				if (p.x > xmin && p.x < xmax  && p.y > ymin && p.y < ymax) {
					
					if (ColorCond[condition][0] == 3) {
						Rectangle(memDC, rect1.left, rect1.top - 2, rect1.right, rect1.bottom + 2);
						Rectangle(memDC, rect2.left - 2, rect2.top, rect2.right + 2, rect2.bottom);
						++points;
						break;
					}
					if (ColorCond[condition][1] == 3) {
						Rectangle(memDC, rect1.left, rect1.top - 2, rect1.right, rect1.bottom + 2);
						//Rectangle(memDC, rect2.left - 2, rect2.top, rect2.right + 2, rect2.bottom);
						--points;
						break;
					}
					break;
			}
		}

		BitBlt(hdc, 0, 0, bmpWidth, bmpHeight, memDC, 0, 0, SRCCOPY);
		
		DeleteObject(whitepen);
		DeleteObject(redpen);
		DeleteObject(greenpen);
		DeleteObject(bluepen);
		DeleteObject(nullpen);
		DeleteObject(whitebrush);
		DeleteObject(redbrush);
		DeleteObject(greenbrush);
		DeleteObject(bluebrush);
		DeleteObject(blackbrush);
		DeleteObject(bmp);
		DeleteDC(memDC);


		auto t2 = std::chrono::high_resolution_clock::now();
		int sleeptime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		if (sleeptime < flicktime) {
			std::this_thread::sleep_for(std::chrono::microseconds(flicktime - sleeptime));
		}

		InvalidateRect(hWnd, NULL, TRUE);
	}

	
	ShowCursor(TRUE);//shows it again
	return points;
}

/*int a = rect1.left;
int b = rect1.top;
int c = rect1.right;
for (int i = 0; i < 30; i++) {
SetPixel(hdc, a, b, RGB(0xff, 0xff, 0xff));
SetPixel(hdc, c, b, RGB(0xff, 0xff, 0xff));
a = a + 1;
b = b + 1;
c = c - 1;
for (int j = 0; j < 8; j++) {
SetPixel(hdc, a+j, b, RGB(0xff, 0xff, 0xff));
SetPixel(hdc, c - j, b, RGB(0xff, 0xff, 0xff));
}
}*/
/*Pen white(Color(255, 255, 255, 255), 8);
gr.DrawLine(&white, rect1.left, rect1.top, rect1.right, rect1.bottom);
gr.DrawLine(&white, rect1.left, rect1.bottom, rect1.right, rect1.top);*/
//SelectObject(memDC, greybrush);




//HBITMAP positive = CreateCompatibleBitmap(hdc, nShip, nShip);

//HBITMAP sprites = (HBITMAP)LoadImage(0, _T("green.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////BITMAP bm;
////HBITMAP sprites = (HBITMAP)LoadBitmap(NULL, MAKEINTRESOURCE(_T("green.bmp")));
//GetObject(sprites, sizeof(positive), &positive);

//HDC memDC2 = CreateCompatibleDC(hdc);
//
//SelectObject(memDC2, sprites);

//BitBlt(hdc, p.x - nShip / 2, p.y - nShip / 2, nShip, nShip, memDC2, 0, 0, SRCCOPY); //LR_LOADFROMFILE);

//DeleteObject(sprites);
//DeleteDC(memDC2);
//