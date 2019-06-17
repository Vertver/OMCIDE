/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Dynamic symbol libraries
*********************************************************/
#include "../Platform.h"

void*
OMCGetProc(
	void* LibHandle,
	const char* ProcName
)
{
	return GetProcAddress((HMODULE)LibHandle, ProcName);
}

void*
OMCLoadLibrary(
	const char* LibraryName
)
{
	HMODULE hLib = NULL;
	WCHAR szLibrary[260] = { 0 };

	/*
		HACK: we can load any library from any path we want.
		We use wide char strings because some of people use other
		langs.
	*/
	hLib = GetModuleHandleA(LibraryName);
	if (hLib == NULL || hLib == INVALID_HANDLE_VALUE)
	{
		if (MultiByteToWideChar(CP_UTF8, 0, LibraryName, strlen(LibraryName), szLibrary, 260))
		{
			hLib = LoadLibraryW(szLibrary);
		}
	}

	return hLib;
}

void
OMCFreeLibrary(
	void* LibraryHandle
)
{
	/*
		Free only existed library. 0 - process instance, we can't free it
	*/
	if (LibraryHandle != NULL && LibraryHandle != INVALID_HANDLE_VALUE)
	{
		FreeLibrary((HMODULE)LibraryHandle);
	}
}