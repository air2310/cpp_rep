#include <Windows.h> // windows API that allows us to create a window
#include <d3d9.h>
#include <vector>
#include <algorithm>   // randon shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <stdlib.h> 
#include <thread>
#include <chrono>		//time
#include <objidl.h>
#include <gdiplus.h>
#include <iostream> //display things if I want
#include <sstream> //strings
#include <string>
#include <stdio.h>
#include "C:\Program Files\MATLAB\R2015a\extern\include\mat.h"
#include "stdafx.h"
#include "fixationcross.h"

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib, "d3d9.lib")

#define WM_COMMAND                      0x0111
#define IDC_RED_BUTTON 101
#define IDC_GREEN_BUTTON 102
#define IDC_BLUE_BUTTON 103
#define BUFSIZE 256 //#define BUFSIZE 256
#define port 53328

// For InpOut
typedef void(__stdcall *lpOut32)(short, short);
typedef short(__stdcall *lpInp32)(short);
typedef BOOL(__stdcall *lpIsInpOutDriverOpen)(void);
//typedef BOOL(__stdcall *lpIsXP64Bit)(void);

//Some global function pointers (messy but fine for this)
lpOut32 gfpOut32;
lpInp32 gfpInp32;
lpIsInpOutDriverOpen gfpIsInpOutDriverOpen;
//lpIsXP64Bit gfpIsXP64Bit;


HWND ghMainWnd = 0;

int nWidth(1920); //screen
int nHeight(1080);

int Xwidth = 50;
int Xheight = 10;
int Xx = (nWidth/2)-(Xwidth/2); //fixation cross
int Xy = (nHeight / 2) - (Xheight / 2);

int Swidth = 100;
int Sheight = 100;
int Sx = (nWidth / 2) - (Swidth / 2); //Stimuli
int Sy = (nHeight / 2) - (Sheight / 2);


size_t size = 12; // Number or square presentations

int myrandom(int i) { return std::rand() % i; }
const int TIMER = 1;

int flicktime = 16700; //microseconds per frame for 60Hz
int TRIALS = 0;
int NTRIALS = 3;
int ANS;

int fixation = 1;
int trialstart = 2;
int question = 3;
int correct = 4;
int wrong = 5;


std::vector<double> create_reps(const size_t N) { //Lets try figure out which color repeats
	std::vector<double> reps(N);
	for (size_t i = 0; i < N; i++) {
		if (i < N / 3) {
			reps[i] = 1;
		}
		else if ((i >((N / 3) - 1)) && (i < (N / 3) * 2)) {
			reps[i] = 2;
		}
		else if ((i > ((N / 3) - 1) * 2) && (i < N)) {
			reps[i] = 3;
		}
	}

	std::srand(unsigned(std::time(0))); //randomiser
	std::random_shuffle(reps.begin(), reps.end(), myrandom); //randomly shuffle elements
	return reps;
}

std::vector<double> reps = create_reps(NTRIALS);


char *file = "Colourepeated.mat";
char str[BUFSIZE];
int status;
int matcreate() {
	MATFile *pmat;
	mxArray *pa1;
			
	pmat = matOpen(file, "w");

	pa1 = mxCreateDoubleMatrix(NTRIALS, 1, mxREAL);

	memcpy((void *)mxGetPr(pa1), reps.data(), NTRIALS*sizeof(double));
	status = matPutVariable(pmat, "Colrep", pa1);

	mxDestroyArray(pa1);
	matClose(pmat);
	return 0;
}



std::vector<int> create_order(const size_t N, double CRep) { //Lets try figure out the order of color presentation
	std::vector<int> order(N);
	for (size_t i = 0; i < size; i++) {
		if (i < size / 3) {
			order[i] = 1;
		}
		else if ((i >((size / 3) - 1)) && (i < (size / 3) * 2)) {
			order[i] = 3;
		}
		else if ((i >((size / 3) - 1) * 2) && (i < size)) {
			order[i] = 2;
		}

	}

	std::srand(unsigned(std::time(0))); //randomiser
	std::random_shuffle(order.begin(), order.end(), myrandom); //randomly shuffle elements

	int loopdiLoop = 1; //Toss out repititions
	while (loopdiLoop <= 1) {
		for (size_t i = 0; i < (size - 1); i++) {
			if (order[i] == order[i + 1]) {
				int iRand = rand() % 12;
				std::swap(order[i], order[iRand]);
				break;
			}
			if (i == (size - 2)) {
				loopdiLoop++;
			}
		}
	}

	int dispnum = rand() % ((size / 3) - 1) + 1;
	int counter = 0;
	for (size_t i = 0; i < (size - 1); i++) { //Make a set of elements consequetive
		if (order[i] == CRep) {
			++counter;
			if (counter == dispnum) {
				for (size_t j = i + 1; j < size; j++) {
					if (order[j] == CRep) {
						std::swap(order[i + 1], order[j]);
						goto theEnd;
					}
				}
			}
		}
	}
theEnd:

	return order;
}


int triggers(int trig)
{
	HINSTANCE hInpOutDll;
	hInpOutDll = LoadLibrary("InpOutx64.DLL");	//The 32bit DLL. If we are building x64 C++ 
												//applicaiton then use InpOutx64.dll
	if (hInpOutDll != NULL)
	{
		gfpOut32 = (lpOut32)GetProcAddress(hInpOutDll, "Out32");
		gfpInp32 = (lpInp32)GetProcAddress(hInpOutDll, "Inp32");
		gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");

		if (gfpIsInpOutDriverOpen())
		{
			gfpOut32(port, 0);
			
			if (trig == fixation) {
				gfpOut32(port, 10);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				gfpOut32(port, 0);
			}
			if (trig == trialstart) {
				gfpOut32(port, 20);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				gfpOut32(port, 0);
			}
			if (trig == question) {
				gfpOut32(port, 30);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				gfpOut32(port, 0);
			}
			if (trig == correct) {
				gfpOut32(port, 40);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				gfpOut32(port, 0);
			}
			if (trig == wrong) {
				gfpOut32(port, 50);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				gfpOut32(port, 0);
			}

		}
	}

	//All done
	FreeLibrary(hInpOutDll);
	return 0;
}


VOID redbox(HDC hdc, HWND hWnd)
{
	Graphics graphics(hdc);
	SolidBrush redBrush(Color(255, 255, 0, 0));
	Color blackColor(255, 0, 0, 0);
	//UINT uResult;

	graphics.FillRectangle(&redBrush, Sx, Sy, Swidth, Sheight);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	InvalidateRect(hWnd, NULL, TRUE);
	//UpdateLayeredWindow(hWnd, hdc, NULL, NULL, hdc, NULL, BLACKNESS, NULL, NULL);

	//uResult = SetTimer(hWnd,  TIMER, 1000, (TIMERPROC)NULL);  

	graphics.Clear(blackColor);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


VOID greenbox(HDC hdc, HWND hWnd)
{

	Graphics graphics(hdc);
	SolidBrush greenBrush(Color(255, 0, 255, 0));
	Color blackColor(255, 0, 0, 0);
	//UINT uResult;

	graphics.FillRectangle(&greenBrush, Sx, Sy, Swidth, Sheight);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	InvalidateRect(hWnd, NULL, TRUE);
	//UpdateLayeredWindow(hWnd, hdc, NULL,NULL, hdc, NULL, BLACKNESS, NULL, NULL);

	//uResult = SetTimer(hWnd, TIMER, 1000, (TIMERPROC)NULL);

	graphics.Clear(blackColor);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


VOID bluebox(HDC hdc, HWND hWnd)
{
	Graphics graphics(hdc);
	SolidBrush blueBrush(Color(255, 0, 0, 255));
	Color blackColor(255, 0, 0, 0);
	//UINT uResult;

	graphics.FillRectangle(&blueBrush, Sx, Sy, Swidth, Sheight);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	InvalidateRect(hWnd, NULL, TRUE);
	//UpdateLayeredWindow(hWnd, hdc, NULL, NULL, hdc, NULL, BLACKNESS, NULL, NULL);

	//uResult = SetTimer(hWnd, TIMER, 1000, (TIMERPROC)NULL);

	graphics.Clear(blackColor);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


VOID TextPaint(HDC hdc, HWND hWnd)
{

	Gdiplus::Graphics gr(hdc);
	Font font(&FontFamily(L"Arial"), 20);
	Color blackColor(255, 0, 0, 0);
	SolidBrush brush(Color::White);

	//Gdiplus::StringFormat format = new Gdiplus::StringFormat();
	//format.LineAlignment = Gdiplus::StringAlignment::StringAlignmentCenter;
	//Gdiplus::StringFormat format.Alignment = Gdiplus::StringAlignment::StringAlignmentCenter;

	//RectF Rect(0, 0, 32767, 32767);
	//RectF Bounds1, Bounds2;

	//gr.MeasureString(L"PP", &font);

	//int margin = Bounds1.Width * 2 - Bounds2.Width;	
	
	//Status st = gr.DrawString(L"Which was the first colour to appear twice in a row?", -1, &font, format, &brush);
	//SetTextAlign(hdc, GetTextAlign(hdc) & (~TA_CENTER));

	triggers(question); // Send Triggers
	Status st = gr.DrawString(L"Which was the first colour to appear twice in a row?", -1, &font, PointF((nWidth / 2) - 350, Xy), &brush);
	

	std::this_thread::sleep_for(std::chrono::seconds(2));
	gr.Clear(blackColor);
}

VOID Correct(HDC hdc, HWND hWnd)
{

	Gdiplus::Graphics gr(hdc);
	Font font(&FontFamily(L"Arial"), 20);
	Color blackColor(255, 0, 0, 0);
	SolidBrush brush(Color::Yellow);
	triggers(correct); // Send Triggers
	gr.DrawString(L"CORRECT!", -1, &font, PointF(((nWidth / 2) - 50), Xy), &brush);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	InvalidateRect(hWnd, NULL, TRUE);
	gr.Clear(blackColor);
}

VOID Wrong(HDC hdc, HWND hWnd) //, int ans)
{
	Gdiplus::Graphics gr(hdc);
	Font font(&FontFamily(L"Arial"), 20);
	Color blackColor(255, 0, 0, 0);
	SolidBrush brush(Color::WhiteSmoke);
	triggers(wrong); // Send Triggers
	gr.DrawString(L"INCORRECT!", -1, &font, PointF(((nWidth / 2) - 50), Xy), &brush);

	/*int A = ans;
	if (A == 1) {
		gr.DrawString(L"Red", -1, &font, PointF(((nWidth/2)), Xy+50), &brush);
	}
	else if (A == 2) {
		gr.DrawString(L"Green", -1, &font, PointF(((nWidth/2)), Xy+50), &brush);
	}
	else if (A == 3) {
		gr.DrawString(L"Blue", -1, &font, PointF(((nWidth / 2)), Xy+50), &brush);
	}*/

	std::this_thread::sleep_for(std::chrono::seconds(2));
	InvalidateRect(hWnd, NULL, TRUE);
	gr.Clear(blackColor);
}



VOID buttontown(HWND hWnd, HWND hButton) {

	

	hButton = CreateWindowEx(NULL, //Button
		"BUTTON", //Window class is buttons
		"RED", // What the button will say
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, //Use the default buttons
		Xx + 25 - Xwidth, Xy, Xwidth * 2, Xheight * 4, //Button Dimensions
		hWnd,
		(HMENU)IDC_RED_BUTTON,
		GetModuleHandle(NULL),
		NULL);

	hButton = CreateWindowEx(NULL, //Button
		TEXT("BUTTON"), //Window class is buttons
		TEXT("GREEN"), // What the button will say
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, //Use the default buttons
		Xx + 25 - Xwidth - 200, Xy, Xwidth * 2, Xheight * 4, //Button Dimensions
		hWnd,
		(HMENU)IDC_GREEN_BUTTON,
		GetModuleHandle(NULL),
		NULL);
	hButton = CreateWindowEx(NULL, //Button
		TEXT("BUTTON"), //Window class is buttons
		TEXT("BLUE"), // What the button will say
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, //Use the default buttons
		Xx + 25 - Xwidth + 200, Xy, Xwidth * 2, Xheight * 4, //Button Dimensions
		hWnd,
		(HMENU)IDC_BLUE_BUTTON,
		GetModuleHandle(NULL),
		NULL);

}



bool InitWindowsApp(HINSTANCE instanceHandle, int show);
int run();

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) /* A windows callback procedure. */
{
	HDC          hdc;
	PAINTSTRUCT  ps;
	static HWND hButton;

	switch (msg) {
	case WM_PAINT:
	{
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR           gdiplusToken;
		
		// Initialize GDI+.
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		matcreate(); //save order to mat file
		
		
		int T = TRIALS;
		
		if (T > 0) { // Feedback
			if (reps[--T] == ANS) {
				hdc = BeginPaint(hWnd, &ps);
				Correct(hdc, hWnd);
				EndPaint(hWnd, &ps);
			}
		else {
				hdc = BeginPaint(hWnd, &ps);
				Wrong(hdc, hWnd); //, answer);
				EndPaint(hWnd, &ps);
			}
		}
		
		if (TRIALS == NTRIALS) { // End if last trial
			InvalidateRect(hWnd, NULL, TRUE);
			DestroyWindow(ghMainWnd);
			KillTimer(hWnd, TIMER);
			PostQuitMessage(0);
			return 0;
		}

		double CRep = reps[TRIALS]; //Which trial are we up to
		std::vector<int> order = create_order(size, CRep); //get presentation order

		
		triggers(fixation); // Send Triggers
		hdc = BeginPaint(hWnd, &ps);
		fixationcross(hdc, hWnd, Xx, Xy, Xwidth, Xheight);
		EndPaint(hWnd, &ps);

		triggers(trialstart); // Send Triggers
		for (size_t i = 0; i < 12; ++i) //Squares
		{
			if (order[i] == 1) {
				hdc = BeginPaint(hWnd, &ps);
				redbox(hdc, hWnd);
				EndPaint(hWnd, &ps);
			}
			else if (order[i] == 2) {
				hdc = BeginPaint(hWnd, &ps);
				greenbox(hdc, hWnd);
				EndPaint(hWnd, &ps);
			}
			else if (order[i] == 3) {
				hdc = BeginPaint(hWnd, &ps);
				bluebox(hdc, hWnd);
				EndPaint(hWnd, &ps);
			}
		}


		hdc = BeginPaint(hWnd, &ps); // Ending text
		TextPaint(hdc, hWnd);
		EndPaint(hWnd, &ps);

		GdiplusShutdown(gdiplusToken);
		TRIALS = TRIALS + 1;
		
		
		return TRIALS;
	}
	case WM_CREATE:
		
		buttontown(hWnd, hButton);
		break;
	case WM_COMMAND: {

		if (((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED)) {
			int iMID;
			iMID = LOWORD(wParam);
			switch (iMID) {
			case IDC_RED_BUTTON: {
				ANS = 1;
				InvalidateRect(hWnd, NULL, TRUE);
				/*if (TRIALS == NTRIALS) {
					DestroyWindow(ghMainWnd);
					KillTimer(hWnd, TIMER);
					PostQuitMessage(0);
				}
				else {*/
					UpdateWindow(hWnd);
					break;
				//}
			}
			case IDC_GREEN_BUTTON: {
				ANS = 2;
				InvalidateRect(hWnd, NULL, TRUE);
				/*if (TRIALS == NTRIALS) {
					DestroyWindow(ghMainWnd);
					KillTimer(hWnd, TIMER);
					PostQuitMessage(0);
				}*/
				//else {
					UpdateWindow(hWnd);
					break;
				//}
			}
			case IDC_BLUE_BUTTON: {
				ANS = 3;
				InvalidateRect(hWnd, NULL, TRUE);
				/*if (TRIALS == NTRIALS) {
					DestroyWindow(ghMainWnd);
					KillTimer(hWnd, TIMER);
					PostQuitMessage(0);
				}*/
				//else {
					UpdateWindow(hWnd);
					break;
				//}
			}
			default:
				break;
			}
		}

	}
	case WM_TIMER:

		switch (wParam)
		{
		case TIMER:
			// process the 1-second timer 
			return 0;
		}
	case WM_KEYDOWN:  /* Message created when the user tries to close the window - close if press esc*/
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, TIMER);
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
	wc.hIcon = LoadIcon(0, IDI_APPLICATION); /* A handle to the class icon. */
	wc.hCursor = LoadCursor(0, IDC_ARROW);  /* A handle to the class cursor. */
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // BLACK_BRUSH WHITE BRUSH set white background
	wc.lpszMenuName = 0; /* We're not using a menu here */
	wc.lpszClassName = TEXT("NBack Colours"); /* A pointer to a string that contains the class name */
											  //wc.lpszClassName = "BasicWndClass"; /* A pointer to a string that contains the class name */

	if (!RegisterClass(&wc)) /* Register the windows class */
	{
		MessageBox(0, "RegisterClass FAILED", 0, 0);
		return false;
	}

	ghMainWnd = CreateWindow( /* Create the window */
							  //"BasicWndClass",
							  //"Win32Basic",
		TEXT("NBack Colours"),
		NULL,
		WS_POPUP, //
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nWidth,
		nHeight,
		0,
		0,
		instanceHandle,
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
	//GdiplusShutdown(gdiplusToken);
	return(int)msg.wParam;
}

//char numberstring[(((sizeof i) * CHAR_BIT) + 2) / 3 + 2];
//char string2print = sprintf_s(numberstring, "%i", i);

//std::string s = std::to_string(i);

//std::string s = std::to_string(i);
/*wchar_t string[] = L"talk"; //{ (wchar_t)10 };
graphics.DrawString(string, -1, &font, PointF(400, 300), &whiteBrush);
*/