/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Base allocator
*********************************************************/
#pragma once

void
OMCInitAllocator();

void
OMCDestroyAllocator();

void*
OMCMemAlloc(
	u64 SizeOfAllocating
);

void*
OMCMemReAlloc(
	void* BasePtr,
	u64 SizeOfAllocating
);

void*
OMCMemVirtAlloc(
	u64 SizeOfAllocating,
	u64 MemAlign
);

void
OMCMemVirtFree(
	void* PtrToFree
);

void
OMCMemFree(
	void* PtrToFree
);
