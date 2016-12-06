#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <chrono>	//time
#include <thread> //sleep
#include<iostream>
#include <ctime>        // std::time
#include<math.h>
#include <algorithm>   // random shuffle


#include "painting.h"
#include "resource.h"


#pragma comment (lib,"Gdiplus.lib")
#define PI 3.14159265

; using namespace Gdiplus;

HWND ghMainWnd = 0;

// Define Matrix as row of vectors

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

// Refreshrate
int refreshrate = 60;
int flicktime = 1000000/refreshrate; //microseconds per frame for 60Hz

struct Pointstruct
{
public:
	int H;
	int D;
} ;


//ScreenSize
class sizes {
public:
	int nWidth = 1280;
	int nHeight = 1024;
	int xxtra = (nWidth - nHeight) / 2;
	int border = 8;
};
sizes screen;

//Settings
int myrandom(int i) { return std::rand() % i; }

int nShip = 71; // Ship Size
int nAst = 36;

int AstSpeed = 8;

int nBlocks = 14;
int nTrials = 168;
int nTrialsBlock = 12;

int choosenFrames(int refreshrate) {
	if (refreshrate == 60) {
		int nFrames = 900;
		return nFrames;
	}
	else if (refreshrate == 120) {
		int nFrames = 1800;
		return nFrames;
	}
}
int nFrames = choosenFrames(refreshrate);

int nFreqs = 4;
std::vector<int> createFreqs(int nFreqs) {
	std::vector<int> Freqs(nFreqs);
	Freqs[0] = 8;
	Freqs[1] = 10;
	Freqs[2] = 12;
	Freqs[3] = 15;

	return Freqs;
}
std::vector<int> Freqs = createFreqs(nFreqs); //get movement angles

std::vector<Row> Flicker = CreateFlicker(nFrames, nFreqs, Freqs, refreshrate);

// Set up ColCond
int nCond = 6;
std::vector<Row> ColorCond = CreateColorCond();

std::vector<int> Createorder(int nBlocks, int nCond, int myrandom(int i)) {
	std::srand(unsigned(std::time(0))); //randomiser
	

	std::vector<int> Order(nBlocks);
	int count = 0;
	for (int T = 0; T < floor(nBlocks/nCond); T++) {
		for (int C = 0; C <nCond; C++) {
			Order[count] = C;
			count = count++;
		}
	}

	if ((nCond*floor(nBlocks / nCond)) < nBlocks) {
		int count = nCond*floor(nBlocks / nCond);
		int start = count;
		for (int C = start; C < nBlocks; C++) {
			Order[count] = rand() % 6;
			count = count++;
		}
	}

	std::random_shuffle(Order.begin(), Order.end(), myrandom); //randomly shuffle elements

	return Order;
}

std::vector<int> Order = Createorder(nBlocks, nCond, myrandom); //get movement angles

// Set Asteroids up

std::vector<int> CreateAstAngles(int nAst) {
	std::srand(unsigned(std::time(0))); //randomiser

	std::vector<int> AstAngles(nAst);

	for (int A = 0; A < nAst; A++) {
		AstAngles[A] = rand() % 360 + 1;
	}
	return AstAngles;
}
std::vector<int> AstAngles = CreateAstAngles(nAst); //get movement angles

std::vector<double> CreateXinc(int nAst) {
	std::vector<double> Xinc(nAst);
	for (int A = 0; A < nAst; A++) {
		Xinc[A] = cos(AstAngles[A] * (PI / 180.0))*AstSpeed;
	}
	return Xinc;
}
std::vector<double> Xinc = CreateXinc(nAst);

std::vector<double> CreateYinc(int nAst) {
	std::vector<double> Yinc(nAst);
	for (int A = 0; A < nAst; A++) {
		Yinc[A] = sin(AstAngles[A] * (PI / 180.0))*AstSpeed;
	}
	return Yinc;
}
std::vector<double> Yinc = CreateYinc(nAst);


std::vector<Row> AstX = PreAllocateAst(nAst,nFrames, screen.nHeight, screen.nHeight, nShip, AstSpeed,Xinc);
std::vector<Row> AstY = PreAllocateAst(nAst,nFrames, screen.nHeight, screen.nHeight, nShip, AstSpeed, Yinc); //This is such a dodgy workaround, fix it by just tossing out x and y and only calculating one. Seriously!!!!!!!!!


bool InitWindowsApp(HINSTANCE instanceHandle, int show); //initialise program (see below)
int run(); //Start sending messages (see below)

int WINAPI WinMain(HINSTANCE hInstance, /* A handle to the current instance of the application. */
	HINSTANCE hPrevInstance, /* A handle to the previous instance of the application. */
	PSTR pCmdLine,  /* The command line for the application, excluding the program name. */
	int iShowCmd) /* Controls how the window is to be shown. */
{
	
	if (!InitWindowsApp(hInstance, iShowCmd))
	{
		return 0;
	}
	return run();
}




//Pointstruct structures() {
//	Pointstruct points;
//	int a, b;
//
//	a = 10;
//	b = 20;
//	points.H = a;
//	points.D = b;
//
//	return(points);
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) /* A windows callback procedure. */
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (msg) {

	case WM_PAINT:
	{
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR           gdiplusToken;

		// Initialize GDI+.
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


		//hdc = BeginPaint(hWnd, &ps);

		//Pointstruct points = structures();

		//EndPaint(hWnd, &ps);
		
		for (int B = 0; B < nBlocks; B++) {

			hdc = BeginPaint(hWnd, &ps);
			cue(hdc, hWnd, screen.nWidth, nShip, screen.nHeight, screen.xxtra, screen.border, ColorCond, B, Order);
			EndPaint(hWnd, &ps);

			for (int T = 0; T < nTrialsBlock; T++) {

				hdc = BeginPaint(hWnd, &ps);
				
				int trialpoints = Trial(hdc, hWnd, screen.nWidth, nShip, screen.nHeight, screen.xxtra, screen.border, flicktime, nFrames, nAst, AstX, AstY, ColorCond, B, Order, Flicker);
				EndPaint(hWnd, &ps);

				hdc = BeginPaint(hWnd, &ps);
				Feedback(hdc, hWnd, trialpoints, screen.nWidth, nShip, screen.nHeight, screen.xxtra, screen.border, ColorCond, B, Order);//trialpoints);
				EndPaint(hWnd, &ps);
			}
		}

		GdiplusShutdown(gdiplusToken);
		DestroyWindow(ghMainWnd);
		PostQuitMessage(0);
	}
	case WM_KEYDOWN:  /* Message created when the user tries to close the window - close if press esc*/
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}




bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{

	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;  /* The class style(s) */
	wc.lpfnWndProc = WndProc;  /* A pointer to the window procedure. */ // N.B. here we specify the name of our function
	wc.cbClsExtra = 0;  /* The number of extra bytes to allocate following the window-class structure. */
	wc.cbWndExtra = 0; /* The number of extra bytes to allocate following the window instance. */
	wc.hInstance = instanceHandle;  /* A handle to the instance that contains the window procedure for the class. */
	wc.hIcon = LoadIcon(0, IDI_WINLOGO); /* A handle to the class icon. */
	wc.hCursor = 0;//LoadCursor(0, IDC_ARROW);  /* A handle to the class cursor. */
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // BLACK_BRUSH WHITE BRUSH set white background
	wc.lpszMenuName = 0; /* I'm not using a menu*/
	wc.lpszClassName = TEXT("Asteroids"); /* A pointer to a string that contains the class name */
											  //wc.lpszClassName = "BasicWndClass"; /* A pointer to a string that contains the class name */

	if (!RegisterClass(&wc)) /* Register the windows class */
	{
		MessageBox(0, "RegisterClass FAILED", 0, 0);
		return false;
	}
	ghMainWnd = CreateWindow( // Create the window //"BasicWndClass", //"Win32Basic",
		TEXT("Asteroids"),  /* A pointer to a string that contains the class name */
		NULL, //Name of Window
		WS_POPUP, // Window Style
		0, //xposition of window on screen
		0, //Yposition of window on screen
		screen.nWidth, //Width of Window
		screen.nHeight, //Height of Window
		0,
		0,
		instanceHandle, //hinsystance
		0);

	if (ghMainWnd == 0)
	{
		MessageBox(0, "Window failed to create", "Error", MB_OK);
		return false;
	}

	

	/* The window is initially hidden, we need to show it */
	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);
	return true;
}

// The main message loop 
int run()
{
	MSG msg = { 0 };
	BOOL bRet = 1;
	while ((bRet == GetMessage(&msg, 0, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			MessageBox(0, "Getmessage Failed", "Error", MB_OK);
			break;
		}
		else
		{
			/* translate and dispatch the message */
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return(int)msg.wParam;
}