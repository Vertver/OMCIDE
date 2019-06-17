/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Thread System
*********************************************************/
#pragma once
#include "../Platform.h"

typedef void ThreadFunc(void *);

typedef struct tagTHREAD_INFO
{
	u32 ThreadId;
	u32 ThreadPriority;
	void* hThread;
	void* pArgs;
	ThreadFunc* pFunc;
	const char* lpThreadName;
} THREAD_INFO, *PTHREAD_INFO;

boolean
OMCIsMainThread();

void*
OMCCreateThread(
	ThreadFunc* pFunc,
	THREAD_INFO* threadInfo
);

void
OMCTerminateThread(
	void* ThreadHandle,
	u32 ExitCode
);

u32
OMCGetThreadId(
	void* ThreadHandle
);

u32
OMCGetMainThreadId();