/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Dynamic symbol libraries
*********************************************************/
#pragma once

void*
OMCGetProc(
	void* LibHandle, 
	const char* ProcName
);

void*
OMCLoadLibrary(
	const char* LibraryName
);

void
OMCFreeLibrary(
	void* LibraryHandle
);