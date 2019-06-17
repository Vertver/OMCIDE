/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Entry-point
*********************************************************/
#include "../Platform.h"

int
OMCMain(
	char** argv,
	int argc
)
{
	OMCRenderInit(0);
	OMCSetInited();

	while (true)
	{
		Sleep(1);

		if (!OMCIsEnabled())
		{
			break;
		}
	}

	OMCRenderDestroy();

	return 0;
}
