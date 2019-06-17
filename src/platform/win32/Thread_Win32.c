/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Thread System
*********************************************************/
#include "Thread.h"

u32 ThreadId = 0;
u32 ThreadCount = 0;

boolean
OMCIsMainThread()
{
	return (GetCurrentThreadId() == ThreadId);
}

DWORD
OMCThreadFunc(
	void* pArgs
)
{
	THREAD_INFO* threadInfo = (THREAD_INFO*)pArgs;

	threadInfo->hThread = GetCurrentThread();
	threadInfo->ThreadId = GetCurrentThreadId();
	
	SetThreadPriority(threadInfo->hThread, threadInfo->ThreadPriority);
	threadInfo->pFunc(threadInfo->pArgs);

	return 0;
}

void*
OMCCreateThread(
	ThreadFunc* pFunc,
	THREAD_INFO* threadInfo
)
{
	void* hThread = NULL;
	THREAD_INFO tempInfo;
	
	if (!threadInfo)
	{
		memset(&tempInfo, 0, sizeof(THREAD_INFO));
		threadInfo = &tempInfo;
	}
	
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pFunc, threadInfo, 0, &threadInfo->ThreadId);

	return hThread;
}

void
OMCTerminateThread(
	void* ThreadHandle,
	u32 ExitCode
)
{
	if (ThreadHandle != NULL && ThreadHandle != INVALID_HANDLE_VALUE)
	{
		TerminateThread(ThreadHandle, ExitCode);
	}
}

u32
OMCGetThreadId(
	void* ThreadHandle
) 
{
	return GetCurrentThreadId();
}

u32
OMCGetMainThreadId()
{
	if (!ThreadId)
	{
		ThreadId = GetCurrentThreadId();
	}

	return ThreadId;
}
