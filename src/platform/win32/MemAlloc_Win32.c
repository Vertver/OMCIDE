/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Base allocator
*********************************************************/
#include "../Platform.h"

#ifdef WINDOWS_PLATFORM
HANDLE hHeap;

void
OMCInitAllocator()
{
	hHeap = HeapCreate(0, 0x010000, 0);
}

void*
OMCMemAlloc(
	u64 SizeOfAllocating
)
{
	return HeapAlloc(hHeap, 0, SizeOfAllocating);
}

void*
OMCMemReAlloc(
	void* BasePtr,
	u64 SizeOfAllocating
)
{
	return HeapReAlloc(hHeap, 0, BasePtr, SizeOfAllocating);
}

void*
OMCMemVirtAlloc(
	u64 SizeOfAllocating,
	u64 MemAlign
)
{
	return VirtualAlloc(NULL, ALIGN_SIZE(SizeOfAllocating, MemAlign), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void
OMCMemVirtFree(
	void* PtrToFree
)
{
	if (PtrToFree != NULL && PtrToFree != INVALID_HANDLE_VALUE)
	{
		VirtualFree(PtrToFree, 0, MEM_RELEASE);
	}
}

void
OMCMemFree(
	void* PtrToFree
)
{
	if (PtrToFree != NULL && PtrToFree != INVALID_HANDLE_VALUE)
	{
		HeapFree(hHeap, 0, PtrToFree);
	}
}
#endif