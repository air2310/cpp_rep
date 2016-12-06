#include <Windows.h>
#include "triggers.h";


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
#define port 53328

int trigger(int trig)
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
			gfpOut32(port, trig);
			
		}
	}

	//All done
	FreeLibrary(hInpOutDll);
	return 0;
}



//int triggerinit(int trig)
//{
//	HINSTANCE hInpOutDll;
//	hInpOutDll = LoadLibrary("InpOutx64.DLL");	//The 32bit DLL. If we are building x64 C++ 
//												//applicaiton then use InpOutx64.dll
//	if (hInpOutDll != NULL)
//	{
//		gfpOut32 = (lpOut32)GetProcAddress(hInpOutDll, "Out32");
//		gfpInp32 = (lpInp32)GetProcAddress(hInpOutDll, "Inp32");
//		gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");
//
//		if (gfpIsInpOutDriverOpen())
//		{
//			gfpOut32(port, 0);
//
//			gfpOut32(port, trig);
//			//std::this_thread::sleep_for(std::chrono::milliseconds(200));
//			gfpOut32(port, 0);
//
//
//		}
//	}
//
//	//All done
//	FreeLibrary(hInpOutDll);
//	return 0;
//}

