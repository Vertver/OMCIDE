/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Entry-point
*********************************************************/
#include "../Platform.h"

boolean 
InitMainRender()
{
	int Counter = 0;

InitRenders:
	if (Counter < MAX_RENDERS)
	{
		if (!OMCRenderInit(Counter))
		{
			OMCRenderDestroy();
			OMCWindowDestroy(OMCGetMainWindowHandle());

			Counter++;
			goto InitRenders;
		}
		
		OMCSetInited();
		return true;
	}

	return false;
}

int
OMCMain(
	char** argv,
	int argc
)
{
	if (InitMainRender())
	{
		while (true)
		{
			SLEEP(1);

			if (!OMCIsEnabled())
			{
				break;
			}
		}

		OMCRenderDestroy();
	}


	return 0;
}
