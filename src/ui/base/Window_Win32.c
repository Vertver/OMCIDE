/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: Window system
*********************************************************/
#include "../Platform.h"

boolean Window_Flag_Resizeing = false;
boolean FirstResize = true;
HANDLE hCloseEvent = NULL;
HANDLE hWaitForInit = NULL;
HWND MainHWND = NULL;

int
OMCIsEnabled()
{
	return !!MainHWND;
}

LRESULT 
CALLBACK
CustomWindowProc(
	HWND   hWnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		OMCMainWindowDestroy();
	case WM_COPY:
		break;
	case WM_ENTERSIZEMOVE:
		/*
			HACK: with this timer, we can draw window with new size
			while this window in resizing state
		*/
		SetTimer(hWnd, 2, 4, NULL);
		Window_Flag_Resizeing = true;
		return 0;
	case WM_EXITSIZEMOVE:
		KillTimer(hWnd, 2);
		Window_Flag_Resizeing = false;
		return 0;
	case WM_TIMER:
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_INVALIDATE);
		return 0;
	case WM_PAINT:
		if (Window_Flag_Resizeing)
		{
			OMCRenderDraw();
		}
		break;
	case WM_SIZE:
		/*
			We can't resize to 0:0, and that's a reason why
			we don't put resize callback if minimized
		*/
		if (wParam != SIZE_MINIMIZED)
		{
			OMCRenderResize(LOWORD(lParam), HIWORD(lParam));
		}
		else
		{
			Sleep(1);
		}
		return 0;
	case WM_SYSCOMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		Sleep(1);
		break;
	}

	/*
		if nothing there, put this to nuklear 
	*/
	if (NuklearHandleEvent(hWnd, uMsg, wParam, lParam)) return 0;

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

void
WindowCreateFunc(
	void* pArgs
)
{
	void** pHWND = (void**)pArgs;

	WNDCLASSW wc;
	RECT rect = { 0, 0, 640, 480 };
	DWORD style = WS_OVERLAPPEDWINDOW;
	DWORD exstyle = WS_EX_APPWINDOW;
	HWND wnd;
	int running = 1;
	HRESULT hr;
	D3D_FEATURE_LEVEL feature_level;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc;

	/*
		Register our window class
	*/
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = CustomWindowProc;
	wc.hInstance = GetModuleHandleW(0);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"OMCIDE_WINDOW";
	RegisterClassW(&wc);

	AdjustWindowRectEx(&rect, style, FALSE, exstyle);

	/*
		Create window with custom caption
	*/
	wnd = CreateWindowExW(exstyle, wc.lpszClassName, L"Omcide alpha",
		style | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, wc.hInstance, NULL
	);

	MainHWND = wnd;

	/*
		Window process function, because we can
	*/
	while (WaitForSingleObject(hCloseEvent, 0) != WAIT_OBJECT_0)
	{
		MSG message;
		RECT rc;

		/*
			We can't do anything if we don't initialized
		*/
		WaitForSingleObject(hWaitForInit, INFINITE);

		GetWindowRect(MainHWND, &rc);
	
		NuklearInputBegin();

		/*
			Standart Windows message translate. No more.
		*/	
		while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}

		NuklearInputEnd();

		/*
			Draw our application and wait for next time
		*/
		OMCRenderDraw();
		Sleep(4);
	}

	OMCWindowDestroy(MainHWND);
	MainHWND = NULL;
}

/*
	Events for our thread, because multithread code is so hard
*/
void
OMCMainWindowDestroy()
{
	if (hCloseEvent && hCloseEvent != INVALID_HANDLE_VALUE) SetEvent(hCloseEvent);
}

void
OMCSetInited()
{
	if (hWaitForInit && hWaitForInit != INVALID_HANDLE_VALUE) SetEvent(hWaitForInit);
}

void*
OMCMainWindowCreate()
{
	void* ptr = NULL;
	void* ThreadHandle = NULL;

	/*
		Create close event
	*/
	if (hCloseEvent && hCloseEvent != INVALID_HANDLE_VALUE) CloseHandle(hCloseEvent);
	hCloseEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	hWaitForInit = CreateEventW(NULL, TRUE, FALSE, NULL);

	THREAD_INFO tInfo;
	memset(&tInfo, 0, sizeof(THREAD_INFO));
	tInfo.pArgs = &ptr;

	/*
		Create window in other thread, because we don't want to 
		run it at main thread
	*/
	ThreadHandle = OMCCreateThread((ThreadFunc*)WindowCreateFunc, &tInfo);

	while (!MainHWND)
	{
		Sleep(1);
	}

	return MainHWND;
}

void
OMCWindowDestroy(
	void* WindowHandle
)
{
	/*
		We can't destroy NULL or invalid handle, right?
	*/
	if (WindowHandle != NULL && WindowHandle != INVALID_HANDLE_VALUE)
	{
		DestroyWindow(WindowHandle);
		if (hCloseEvent && hCloseEvent != INVALID_HANDLE_VALUE) CloseHandle(hCloseEvent);
		if (hWaitForInit && hWaitForInit != INVALID_HANDLE_VALUE) CloseHandle(hWaitForInit);
	}
}

void
OMCMainWindowSetName(
	const char* NameUTF8
)
{
	// get size of new UTF-8 string
	int StringSize = WideCharToMultiByte(CP_UTF8, 0, NameUTF8, -1, NULL, 0, NULL, NULL);
	LPCWSTR lpOutString = NULL;

	if (StringSize)
	{
		/*
			Allocate string and convert to UTF-8
		*/
		lpOutString = OMCMemAlloc(++StringSize);

		if (WideCharToMultiByte(CP_UTF8, 0, NameUTF8, -1, lpOutString, StringSize, NULL, NULL))
		{
			SetWindowTextW(MainHWND, lpOutString);
		}

		OMCMemFree(lpOutString);
	}
}
