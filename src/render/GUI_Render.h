/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: GUI Render
*********************************************************/
#pragma once
#include "../Platform.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION

boolean
OMCRenderInit(
	int RenderType
);

void
OMCRenderRestart(
	int RenderType
);

void
OMCRenderDestroy();

boolean
OMCRenderDraw();

boolean
OMCRenderResize(
	int Width,
	int Height
);

int 
OMCRenderGetType();



boolean
OMCRenderInitD3D11();

boolean
OMCRenderInitOGL();

boolean
OMCRenderInitGDI();

void
OMCRenderDestroyD3D11();

void
OMCRenderDestroyOGL();

void
OMCRenderDestroyGDI();

boolean
OMCRenderDrawD3D11();

boolean
OMCRenderDrawOGL();

boolean
OMCRenderDrawGDI();

boolean
OMCRenderResizeD3D11(
	int Width,
	int Height
);

boolean
OMCRenderResizeOGL(
	int Width, 
	int Height
);

boolean
OMCRenderResizeGDI(
	int Width,
	int Height
);

void
OMCRenderNuklear();

int
NuklearHandleEvent(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

int
NuklearInputBegin();

int
NuklearInputEnd();
