/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Kernel Win32
*********************************************************/
#include "../Platform.h"

BOOL
WINAPI 
wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
)
{
	LPSTR* lpOutArgList = NULL;
	LPWSTR* lpArgList = NULL;
	int iCount = 0;
	int iRet = 0;

	/*
		Get 'argv' and 'argc' in widechar to convert
		this string to UTF-8
	*/
	lpArgList = CommandLineToArgvW(lpCmdLine, &iCount);
	lpOutArgList = OMCMemAlloc(sizeof(void*) * iCount);

	/*
		Parse command line and convert to UTF-8
	*/
	for (i32 i = 0; i < iCount; i++)
	{
		u64 sizeOfString = 0;

		if (!!(sizeOfString = wcslen(lpArgList[i])))
		{
			// get size of new UTF-8 string
			int StringSize = WideCharToMultiByte(CP_UTF8, 0, lpArgList[i], -1, NULL, 0, NULL, NULL);

			if (StringSize)
			{
				// allocate string
				lpOutArgList[i] = OMCMemAlloc(StringSize);

				// convert to UTF-8
				if (!WideCharToMultiByte(CP_UTF8, 0, lpArgList[i], -1, lpOutArgList[i], StringSize, NULL, NULL))
				{
					OMCMemFree(lpOutArgList[i]);
					lpOutArgList[i] = NULL;
					continue;
				}
			}
		}
	}

	/*
		Init OLE and COM
	*/
	OleInitialize(NULL);
	CoInitialize(NULL);

	/*
		Run native entry-point
	*/
	iRet = OMCMain(lpOutArgList, iCount);

	/*
		Free all stuff
	*/
	for (i32 i = 0; i < iCount; i++)
	{
		if (lpOutArgList[i]) OMCMemFree(lpOutArgList[i]);
	}
	OMCMemFree(lpOutArgList);

	/*
		Free COM and OLE
	*/
	OleUninitialize();
	CoUninitialize();

	return iRet;
}
