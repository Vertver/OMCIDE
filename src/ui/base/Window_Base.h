/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Window system
*********************************************************/
#pragma once
#include "../Platform.h"

void*
OMCMainWindowCreate();

void
OMCWindowDestroy(
	void* WindowHandle
);

void
OMCMainWindowDestroy();

void
OMCMainWindowSetName(
	const char* NameUTF8
);

void
OMCSetInited();

int
OMCIsEnabled();