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

#include "nuklear.h"
#include "demo/d3d11/nuklear_d3d11.h"

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

void
OMCRenderDraw();

void
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

void
OMCRenderDrawD3D11();

void
OMCRenderDrawOGL();

void
OMCRenderDrawGDI();

void
OMCRenderResizeD3D11(
	int Width,
	int Height
);

void
OMCRenderResizeOGL(
	int Width, 
	int Height
);

void
OMCRenderResizeGDI(
	int Width,
	int Height
);

void
OMCRenderNuklear();
